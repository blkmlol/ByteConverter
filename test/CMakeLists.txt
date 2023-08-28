cmake_minimum_required(VERSION 3.27)

set(THIS ConverterTest)

set(SOURCE
    ConverterTest.cpp    
)

# Создание исполняемого файла 
add_executable(${THIS}  ${SOURCE})

# Связывание исполняемого файла с библиотекой Converter
target_link_libraries(${THIS} PUBLIC
    gtest_main
    gmock_main
    Converter
)

# Определение теста для запуская исполняемого файла как теста.
# Ctest выполнит теперь команду в ${THIS}
add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)