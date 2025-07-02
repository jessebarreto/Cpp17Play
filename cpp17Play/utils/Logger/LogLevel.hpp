#pragma once

#include <cstdint>
#include <string>

namespace cpp17Play {

enum class LogLevel : std::uint8_t { Debug = 0, Info, Warn, Error, Fatal };

std::string logLevelAsString(LogLevel level);

}  // namespace cpp17Play