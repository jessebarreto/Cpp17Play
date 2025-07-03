
add_executable(
    example_HttpServer 
    example_HttpServer.cpp
)
target_link_libraries(
    example_HttpServer
    TcpServer
    LogService
)