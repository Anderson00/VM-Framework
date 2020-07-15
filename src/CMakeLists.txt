cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
set(SOURCE_FILES main.cpp vboxSoap/stdsoap2.cpp vboxSoap/soapC.cpp vboxSoap/soapClient.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vboxSoap")

add_executable(vm-framework ${SOURCE_FILES})
target_link_libraries(vm-framework PUBLIC cxxopts)