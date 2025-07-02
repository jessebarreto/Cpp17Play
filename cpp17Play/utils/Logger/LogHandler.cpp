#include "LogHandler.hpp"

namespace cpp17Play {

LogHandler::LogHandler() = default;

LogHandler::~LogHandler() = default;

LogLevel LogHandler::level() const { return _level; }

void LogHandler::setLevel(LogLevel level) { _level = level; }

}  // namespace cpp17Play