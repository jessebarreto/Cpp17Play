

add_library(
    TcpServer
    STATIC
    TcpServer.hpp
    TcpServer.cpp
)
target_link_libraries(
    TcpServer
    PUBLIC
    LogService
    PRIVATE
    fmt::fmt
    -static-libstdc++
)

add_subdirectory(example)