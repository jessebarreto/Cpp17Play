#include "../LogLevel.hpp"
#include "../LogService.hpp"


int main() {
  LOG(cpp17Play::LogLevel::Fatal, "Log Message");
  SET_LOG_LEVEL(cpp17Play::LogLevel::Debug);

  LOG_FATAL(" for fatal log");
  LOG_ERROR(" for error log");
  LOG_WARN(" for warn log");
  LOG_INFO(" for info log");
  LOG_DEBUG(" for debug log");
}
