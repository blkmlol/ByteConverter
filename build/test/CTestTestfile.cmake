# CMake generated Testfile for 
# Source directory: C:/BLMP/VSC/Converter/test
# Build directory: C:/BLMP/VSC/Converter/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[ConverterTest]=] "C:/BLMP/VSC/Converter/build/test/Debug/ConverterTest.exe")
  set_tests_properties([=[ConverterTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/BLMP/VSC/Converter/test/CMakeLists.txt;21;add_test;C:/BLMP/VSC/Converter/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[ConverterTest]=] "C:/BLMP/VSC/Converter/build/test/Release/ConverterTest.exe")
  set_tests_properties([=[ConverterTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/BLMP/VSC/Converter/test/CMakeLists.txt;21;add_test;C:/BLMP/VSC/Converter/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[ConverterTest]=] "C:/BLMP/VSC/Converter/build/test/MinSizeRel/ConverterTest.exe")
  set_tests_properties([=[ConverterTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/BLMP/VSC/Converter/test/CMakeLists.txt;21;add_test;C:/BLMP/VSC/Converter/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[ConverterTest]=] "C:/BLMP/VSC/Converter/build/test/RelWithDebInfo/ConverterTest.exe")
  set_tests_properties([=[ConverterTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/BLMP/VSC/Converter/test/CMakeLists.txt;21;add_test;C:/BLMP/VSC/Converter/test/CMakeLists.txt;0;")
else()
  add_test([=[ConverterTest]=] NOT_AVAILABLE)
endif()
