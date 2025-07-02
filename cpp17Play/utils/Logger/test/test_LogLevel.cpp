#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "../LogLevel.hpp"

using namespace cpp17Play;

class LogLevelTestFixture
    : public ::testing::TestWithParam<std::pair<LogLevel, std::string>> {
 protected:
  std::pair<LogLevel, std::string> logLevelExpectedStr;
};

TEST_P(LogLevelTestFixture,
       GIVEN_LogLevel_WHEN_ConvertingToString_THEN_ConvertCorrectly) {
  std::pair<LogLevel, std::string> levelExpectedStr = GetParam();

  EXPECT_EQ(logLevelAsString(levelExpectedStr.first), levelExpectedStr.second);
}

INSTANTIATE_TEST_CASE_P(
    LogLevelTest, LogLevelTestFixture,
    ::testing::Values(std::make_pair(LogLevel::Fatal, "FATAL:"),
                      std::make_pair(LogLevel::Error, "ERROR:"),
                      std::make_pair(LogLevel::Warn, "WARNING:"),
                      std::make_pair(LogLevel::Info, "INFO:"),
                      std::make_pair(LogLevel::Debug, "DEBUG:")));