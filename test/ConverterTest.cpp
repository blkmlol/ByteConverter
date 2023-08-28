#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory>
#include <bitset>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

//Интерфейс для ввода
class Source {
public:
    //Виртуальная функция чтения
    virtual char read(const char& data) = 0;
};

//Интерфейс для вывода
class Sink {
public:
    //Виртуальная функция записи
    virtual void write(const char& data) = 0;
};

//Мок-объект для тестирования
class MockSource : public Source {
public:
    MOCK_METHOD(char, read, (const char& data), (override));
};

//Мок-объект для тестирования
class MockSink : public Sink {
public:
    MOCK_METHOD(void, write, (const char& data), (override));
};

class Converter : public Source, public Sink {
    std::thread thread;         //Поток для преобразования
    std::mutex mutex;           //Синхронизация доступа к буферу
    std::condition_variable cv; //Переменная для оповещения о получении данных
    bool running;               //Флаг запуска/остановки
    char buffer;                //Буфер для данных
    std::ostringstream output;  //Поток записи рез-ов преобразователя

    void run() {
        while (running) {
            std::unique_lock<std::mutex> lock(mutex);
            //Ожидание данных
            cv.wait(lock, [this] { return !running || buffer != '\0'; });
            
            if (!running) break; //Выход из цикла

            //Сдвиг битов вправо 6 раз для получения типа
            char type = (buffer >> 6) & 0b11; //Получение типа через побитовое И
            //Побитовое И с полученным буфером
            char data = buffer & 0b00111111;  //Чтение данных с позиции data[0..5]

            //Преобразование в строку в соответствии с типом.
            //И помещение строки в output
            if (type == 0b00) {
                //Преобразование беззнакового числа
                output << "Unsigned: " << static_cast<unsigned int>(data) << '\n';
            }
            else if (type == 0b01) {
                //Преобразование знакового числа
                output << "Signed:   " << static_cast<int>(data) << '\n';
            }
            else if (type == 0b10) {
                //Преобразование буквы
                char letter = 'a' + data;
                output << "Letter:   " << letter << '\n';
            }
            buffer = '\0';
        }
    }

public:
    Converter() : running(false) {}
    
    std::string getOutput(){ return output.str();}

    void start() {
        running = true; //Флаг запуска
        thread = std::thread(&Converter::run, this);
    }

    void stop() {
        running = false; //Флаг остановки
        cv.notify_all(); //Уведомить все ожидающие потоки
        thread.join();   //Ждем завершения потока
    }

    void write(const char& byte) override {
        std::unique_lock<std::mutex> lock(mutex);
        buffer = byte;   //Буфер для записи байта
        cv.notify_one(); //Уведомить поток о данных
    }

    char read(const char& data) {
        //Чтение можно было сделать и сложнее.
        //Но сказано, что если это не указано,
        //то остается на усмотрение исполнителя
        //Я и решил просто байты в вектор положить и из него считать.
        return data;
    }
};

TEST(ConverterTest, ByteConverterTest){
    Converter converter;
    MockSource mockSource;
    MockSink mockSink;

    std::vector<char> bytes;
    bytes.push_back(0b00000110); //Тип 0b00: беззнаковое -> Значение: 6
    bytes.push_back(0b10000011); //Тип 0b10: буква       -> Значение: d
    bytes.push_back(0b01000011); //Тип 0b01: знаковое    -> Значение: 3

    //Запуск преобразования байтов
    converter.start();
    for (auto& byte : bytes){
        //Ожидание вызова чтения и возврат байта оттуда
        EXPECT_CALL(mockSource, read(byte)).Times(1).WillOnce(testing::Return(byte));
        //Чтение байта и сохранение результата
        char readByte = mockSource.read(byte);
        //Соответствуют прочитанный и ожидаемый байт?
        EXPECT_EQ(readByte, byte);
        //Запись прочитанного байта в преобразователь
        converter.write(readByte);
        //Пауза для синхронизации потоков
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    converter.stop();
    //Преобразователь остановлен.

    //Ожидаемый результат
    std::ostringstream expectedOutput;
    //Ожидаемый результтат Unsigned: 6
    expectedOutput << "Unsigned: "<<static_cast<unsigned>(bytes[0] & 0b00111111)<<'\n';
    //Ожидаемый результтат Letter: d
    expectedOutput << "Letter:   "<<static_cast<char>((bytes[1] & 0b00111111) + 'a')<<'\n';
    //Ожидаемый результтат Signed: 3
    expectedOutput << "Signed:   "<<static_cast<int>(bytes[2] & 0b00111111)<<'\n';
    //Проверка равенства ожидаемого и полученного результата
    EXPECT_EQ(expectedOutput.str(), converter.getOutput());
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}