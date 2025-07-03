#include "Logger.hpp"

#include <fmt/chrono.h>
#include <fmt/format.h>

#include <chrono>
#include <iterator>

#include "ConsoleLogHandler.hpp"
#include "LogHandler.hpp"
#include "LogHandlerType.hpp"

namespace cpp17Play {

constexpr const char* CONTEXT_FORMAT = "{}:{} {:%d/%m/%Y@%H:%M:%S}";

Logger::Logger() {
  setLogHandler(LogHandlerType::Console, std::make_unique<ConsoleLogHandler>());
}

void Logger::setLogHandler(LogHandlerType logHandlerType,
                           std::unique_ptr<LogHandler> logHandler) {
  _logHandlers.emplace(logHandlerType, std::move(logHandler));
}

void Logger::rawLog(const std::string& filename, std::size_t lineNumber,
                    LogLevel level, const std::string& text) {
  std::string ctx = fmt::format(CONTEXT_FORMAT, filename, lineNumber,
                                std::chrono::system_clock::now());

  for (const auto& [_, logHandler] : _logHandlers) {
    logHandler->handleLog(level, ctx, text);
  }
}

void Logger::setLevel(LogLevel level, LogHandlerType logHandlerType) {
  auto handlerIter = _logHandlers.find(logHandlerType);
  if (handlerIter != std::end(_logHandlers)) {
    handlerIter->second->setLevel(level);
  }
}

void Logger::setDefaultLevel(LogLevel level) {
  for (auto type : {LogHandlerType::Console, LogHandlerType::File,
                    LogHandlerType::Network, LogHandlerType::Trace}) {
    setLevel(level, type);
  }
}

}  // namespace cpp17Play
