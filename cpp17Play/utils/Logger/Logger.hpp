#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

#include "LogHandler.hpp"
#include "LogHandlerType.hpp"

namespace cpp17Play {

class Logger {
  std::unordered_map<LogHandlerType, std::unique_ptr<LogHandler>> _logHandlers;

 public:
  Logger();

  void rawLog(const std::string& filename, std::size_t lineNumber,
              LogLevel level, const std::string& text);

  void setLogHandler(LogHandlerType logHandlerType,
                     std::unique_ptr<LogHandler> logHandler);

  void setLevel(LogLevel level, LogHandlerType logHandlerType);

  void setDefaultLevel(LogLevel level);
};

}  // namespace cpp17Play