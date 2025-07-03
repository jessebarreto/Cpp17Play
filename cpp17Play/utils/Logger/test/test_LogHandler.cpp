#include <fmt/format.h>
#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "../LogHandler.hpp"

using namespace cpp17Play;

class DummyLoghandler final : public LogHandler {
 protected:
  mutable std::vector<std::string> loggedMessages;

 public:
  DummyLoghandler() = default;

  void handleLog(LogLevel level, const std::string& ctx,
                 const std::string& logText) const override {
    loggedMessages.push_back(
        fmt::format("{} {} {}", logLevelAsString(level), ctx, logText));
  }
};

class LogHandlerTestFixture : public ::testing::TestWithParam<LogLevel> {
 protected:
  LogLevel logLevel;
};

TEST_P(LogHandlerTestFixture, GIVEN_LogLevel_WHEN_SettingLevel_THEN_Sets) {
  LogLevel logLevel = GetParam();

  DummyLoghandler logHandler;
  logHandler.setLevel(logLevel);

  EXPECT_EQ(logHandler.level(), logLevel);
}

INSTANTIATE_TEST_CASE_P(LogHandlerTest, LogHandlerTestFixture,
                        ::testing::Values(LogLevel::Fatal, LogLevel::Error,
                                          LogLevel::Warn, LogLevel::Info,
                                          LogLevel::Debug));