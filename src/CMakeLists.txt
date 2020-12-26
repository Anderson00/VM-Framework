cmake_minimum_required(VERSION 3.1)


if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()



set(SOURCE_FILES
vmcore/virtualbox/soap/IVirtualBox.cpp
vmcore/virtualbox/soap/IAppliance.cpp 
vmcore/virtualbox/soap/ICloudNetwork.cpp 
vmcore/virtualbox/soap/ICloudProviderManager.cpp 
vmcore/virtualbox/soap/IDHCPServer.cpp 
vmcore/virtualbox/soap/IEventSource.cpp 
vmcore/virtualbox/soap/IGuestOSType.cpp
vmcore/virtualbox/soap/IHost.cpp
vmcore/virtualbox/soap/IMachine.cpp
vmcore/virtualbox/soap/IMedium.cpp
vmcore/virtualbox/soap/INATNetwork.cpp
vmcore/virtualbox/soap/IObject.cpp
vmcore/virtualbox/soap/IPerformanceCollector.cpp
vmcore/virtualbox/soap/IProgress.cpp
vmcore/virtualbox/soap/ISession.cpp
vmcore/virtualbox/soap/ISharedFolder.cpp
vmcore/virtualbox/soap/IUnattended.cpp
vmcore/virtualbox/soap/IWebSessionManager.cpp
vmcore/virtualbox/soap/SOAPClientSingleton.cpp
vmcore/virtualbox/soap/IHostUSBDevice.cpp vmcore/virtualbox/soap/IHostUSBDevice.cpp
vmcore/virtualbox/soap/IHostNetworkInterface.cpp
vmcore/virtualbox/soap/IHostVideoInputDevice.cpp
vmcore/virtualbox/soap/IHostUpdate.cpp
vmcore/virtualbox/soap/IHostUSBDeviceFilter.cpp)


add_subdirectory(vboxSoap)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vboxSoap")
include_directories("${PROJECT_SOURCE_DIR}/vmcore/virtualbox/soap")

add_executable(vm-framework main.cpp ${SOURCE_FILES})
target_link_libraries(vm-framework PUBLIC cxxopts vboxSoap) 