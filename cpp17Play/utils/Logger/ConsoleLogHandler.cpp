#include "ConsoleLogHandler.hpp"

#include <fmt/color.h>
#include <fmt/format.h>

#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

#include "LogLevel.hpp"

namespace cpp17Play {

std::unordered_map<LogLevel, fmt::text_style> _LEVELSTYLEMAP{
    {LogLevel::Fatal, fmt::emphasis::bold | fmt::bg(fmt::color::red) |
                          fmt::fg(fmt::color::white)},
    {LogLevel::Error, fmt::fg(fmt::color::red)},
    {LogLevel::Warn, fmt::fg(fmt::color::yellow)},
    {LogLevel::Info, fmt::emphasis::bold},
    {LogLevel::Debug, fmt::fg(fmt::color::blue)},
};

ConsoleLogHandler::ConsoleLogHandler() = default;

void ConsoleLogHandler::handleLog(LogLevel level, const std::string& ctx,
                                  const std::string& logText) const {
  if (level < this->level()) {
    return;
  }

  auto formattedPrefixLevel =
      fmt::format(_LEVELSTYLEMAP.at(level), "{}", logLevelAsString(level));
  auto formattedCtx = fmt::format(fmt::emphasis::bold, "{}", ctx);
  auto formattedText = fmt::format("{}", logText);

  fmt::print(_format, formattedPrefixLevel, formattedCtx, formattedText);
}

}  // namespace cpp17Play