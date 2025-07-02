
add_library(
    LogLevel
    STATIC
    "LogLevel.hpp"
    "LogLevel.cpp"
)

add_library(
    LogHandler
    STATIC
    "LogHandler.hpp"
    "LogHandler.cpp"
)
target_link_libraries(
    LogHandler
    LogLevel
    fmt::fmt
)

add_library(
    ConsoleLoghandler
    STATIC
    "ConsoleLogHandler.hpp"
    "ConsoleLogHandler.cpp"
)
target_link_libraries(
    ConsoleLoghandler
    LogHandler
    fmt::fmt
)

add_library(
    LogHandlerType
    INTERFACE
    "LogHandlerType.hpp"
)

add_library(
    Logger
    STATIC
    "Logger.hpp"
    "Logger.cpp"
)
target_link_libraries(
    Logger
    LogHandler
    LogHandlerType
    fmt::fmt
)

add_library(
    LoggerConfig
    INTERFACE
    "LoggerConfig.hpp"
)

add_library(
    LogService
    STATIC
    "LogService.hpp"
)
target_link_libraries(
    LogService
    Singleton
    Logger
    LogLevel
)

add_subdirectory(example)
add_subdirectory(test)