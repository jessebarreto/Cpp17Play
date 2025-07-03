#pragma once

#include <string>

#include "LogHandler.hpp"
#include "LogLevel.hpp"

namespace cpp17Play {

constexpr const char* DEFAULT_CONSOLE_FORMAT = "{} {} - {}\n";

class ConsoleLogHandler : public LogHandler {
  const std::string _format{DEFAULT_CONSOLE_FORMAT};

 public:
  ConsoleLogHandler();

  void handleLog(LogLevel level, const std::string& ctx,
                 const std::string& logText) const override;
};

}  // namespace cpp17Play
