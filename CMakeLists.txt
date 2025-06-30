cmake_minimum_required(VERSION 3.15...4.0)

project(Cpp17Play 
        VERSION 1.0
        DESCRIPTION "Cpp17 Play"
        LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rd_party)

add_subdirectory(cpp17Play)