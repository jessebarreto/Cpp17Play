enable_testing()

add_executable(
    test_Adapter 
    test_Adapter.cpp
)
target_link_libraries(
    test_Adapter
    Adapter
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_Adapter)