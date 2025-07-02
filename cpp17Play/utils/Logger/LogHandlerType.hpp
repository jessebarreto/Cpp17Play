#pragma once

#include <cstdint>

namespace cpp17Play {

enum class LogHandlerType : std::uint8_t { Console = 0, File, Network, Trace };

}  // namespace cpp17Play