
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

add_executable(
    test_BuilderDirector 
    test_BuilderDirector.cpp
)
target_link_libraries(
    test_BuilderDirector
    BuilderDirector
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_BuilderDirector)

add_executable(
    test_Prototype
    test_Prototype.cpp
)
target_link_libraries(
    test_Prototype
    Prototype
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_Prototype)