enable_testing()

add_executable(
    test_LogLevel
    test_LogLevel.cpp
)
target_link_libraries(
    test_LogLevel
    LogLevel
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_LogLevel)

add_executable(
    test_LogHandler
    test_LogHandler.cpp
)
target_link_libraries(
    test_LogHandler
    LogHandler
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_LogHandler)
