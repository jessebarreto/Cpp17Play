#include "../../utils/Logger/LogService.hpp"
#include "../TcpServer.hpp"

int main() {
  SET_LOG_LEVEL(cpp17Play::LogLevel::Debug);

  const auto ipAddress = "0.0.0.0";
  const auto port = 8080;

  cpp17Play::TcpServer tcpServer(ipAddress, port);

  tcpServer.listen();
}