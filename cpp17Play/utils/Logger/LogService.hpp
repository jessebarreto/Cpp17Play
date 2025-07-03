#pragma once

#include <cstdint>

#include "../../design_pattern/creational_patterns/Singleton.hpp"
#include "LogLevel.hpp"
#include "Logger.hpp"

#define LOG(level, text)                                      \
  cpp17Play::Singleton<cpp17Play::Logger>::instance().rawLog( \
      __FILE__, __LINE__, level, text)

#define LOG_FATAL(text) LOG(cpp17Play::LogLevel::Fatal, text)
#define LOG_ERROR(text) LOG(cpp17Play::LogLevel::Error, text)
#define LOG_WARN(text) LOG(cpp17Play::LogLevel::Warn, text)
#define LOG_INFO(text) LOG(cpp17Play::LogLevel::Info, text)
#define LOG_DEBUG(text) LOG(cpp17Play::LogLevel::Debug, text)

#define SET_LOG_LEVEL(level) \
  cpp17Play::Singleton<cpp17Play::Logger>::instance().setDefaultLevel(level)
