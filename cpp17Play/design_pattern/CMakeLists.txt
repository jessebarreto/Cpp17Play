
add_library(
    AbstractFactory
    INTERFACE
    "AbstractFactory.hpp"
)

add_library(
    Singleton
    INTERFACE
    "Singleton.hpp"
    # SHARED
    # "Singleton.cpp"
)

add_subdirectory(test)