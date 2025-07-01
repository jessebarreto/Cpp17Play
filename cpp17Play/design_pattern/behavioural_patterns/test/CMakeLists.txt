
enable_testing()

add_executable(
    test_ChainOfResponsibility 
    test_ChainOfResponsibility.cpp
)
target_link_libraries(
    test_ChainOfResponsibility
    ChainOfResponsibility
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_ChainOfResponsibility)