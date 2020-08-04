cmake_minimum_required(VERSION 3.1)
project(VM-Framework)
enable_testing() 

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED true)


SET(gtest_force_shared_crt ON CACHE BOOL "testando")
#option(gtest_force_shared_crt "option" ON)
#SET(gtest_force_shared_crt "ON" CACHE bool)
message(${gtest_force_shared_crt})

SET(VMCORE_SOAP_DIR ${PROJECT_SOURCE_DIR}/src/vmcore/virtualbox/soap)

include(GoogleTest)
add_subdirectory(extern/cxxopts)
add_subdirectory(src)
add_subdirectory(test)