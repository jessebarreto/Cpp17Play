
enable_testing()

add_executable(
    test_AbstractFactory 
    test_AbstractFactory.cpp
)
target_link_libraries(
    test_AbstractFactory
    AbstractFactory
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_AbstractFactory)

add_executable(
    test_Singleton 
    test_Singleton.cpp
)
target_link_libraries(
    test_Singleton
    Singleton
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_Singleton)