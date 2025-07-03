#pragma once

#include <string>

#include "LogLevel.hpp"

namespace cpp17Play {

class LogHandler {
  LogLevel _level{LogLevel::Fatal};

 protected:
  LogHandler();

 public:
  virtual ~LogHandler();

  LogHandler(LogHandler&&) = delete;
  LogHandler& operator=(LogHandler&&) = delete;
  LogHandler(LogHandler&) = delete;
  LogHandler& operator=(LogHandler&) = delete;

  [[nodiscard]] LogLevel level() const;
  void setLevel(LogLevel level);

  virtual void handleLog(LogLevel level, const std::string& ctx,
                         const std::string& logText) const = 0;
};

}  // namespace cpp17Play