cmake_minimum_required(VERSION 3.27)

set(THIS Converter)

project(${THIS} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(SOURCE
    test.cpp    
)

# Создание статической библиотеки с именем Converter из исходных cpp файлов
add_library(${THIS} STATIC ${SOURCE})

# Добавление подкаталога "test" для сборки тестов
add_subdirectory(test)