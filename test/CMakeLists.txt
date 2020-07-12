
add_subdirectory("../extern/googletest" "extern/googletest")

add_executable(tests test.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include")

target_link_libraries(tests gtest gmock gtest_main)
set_target_properties(tests PROPERTIES FOLDER test)


gtest_discover_tests(tests
        # set a working directory so your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )