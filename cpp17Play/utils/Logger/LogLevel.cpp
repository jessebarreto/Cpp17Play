#include "LogLevel.hpp"

namespace cpp17Play {

std::string logLevelAsString(LogLevel level) {
  switch (level) {
    case LogLevel::Error:
      return "ERROR:";
    case LogLevel::Warn:
      return "WARNING:";
    case LogLevel::Info:
      return "INFO:";
    case LogLevel::Debug:
      return "DEBUG:";
    default:
      return "FATAL:";
  }
}

}  // namespace cpp17Play