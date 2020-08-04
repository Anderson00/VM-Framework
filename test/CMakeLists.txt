
add_subdirectory("../extern/googletest" "extern/googletest")
file(GLOB FILES "../src/vmcore/virtualbox/soap/*.cpp")

link_directories(../src/vmcore/virtualbox/soap)

add_executable(tests test.cpp ${FILES})

include_directories("${VMCORE_SOAP_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include")
include_directories("${CMAKE_SOURCE_DIR}/extern/cxxopts/include")
include_directories("../src/vboxSoap")
include_directories("../src/vmcore/virtualbox/soap")

target_link_libraries(tests gtest gmock gtest_main cxxopts vboxSoap)
set_target_properties(tests PROPERTIES FOLDER test)


gtest_discover_tests(tests
        # set a working directory so your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )