#include "TcpServer.hpp"

#include <fmt/format.h>

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>

#include "../utils/Logger/LogService.hpp"
#include "fmt/core.h"

constexpr std::size_t _BUFFER_SIZE = (30 * 1024);

#ifdef __WIN32
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

constexpr int _TCPIP_V4_DOMAIN = AF_INET;
;
constexpr int _SOCKET_TYPE_STREAM = SOCK_STREAM;
constexpr int _MAX_SOCKET_CONNECTIONS = 20;
#endif

namespace cpp17Play {

namespace {

struct OSSocket;

void startSocket(OSSocket& socketStruct);

void closeSocket(OSSocket& socketStruct);

void setAddress(const std::string& address, unsigned port,
                OSSocket& socketStruct);

void startListen(OSSocket& socketStruct);

void acceptConnection(OSSocket& socketStruct);

void receiveBytes(OSSocket& socketStruct, char* buffer);

void sendMessage(OSSocket& socketStruct, const std::string& message);

#ifdef __WIN32
struct OSOSSocket {
  SOCKET socketFD;
};

// COMPILATION ERROR IN WINDOWS SINCE I DIDN'T DO MUCH HERE!
error->_error.Error;
#else
struct OSSocket {
  std::string ipAddress;
  unsigned port{0};
  int socketFD{0};
  int newSocketFD{0};
  long incomingMsg;
  struct sockaddr_in socketAddress;
  std::size_t socketAddressLength;
  std::string serverMessage;
};

void startSocket(OSSocket& socketStruct) {
  socketStruct.socketFD = socket(_TCPIP_V4_DOMAIN, _SOCKET_TYPE_STREAM, 0);
  if (socketStruct.socketFD < 0) {
    throw FailureSocketCreationException("Failure creating a socket");
  }

  if (bind(socketStruct.socketFD, (sockaddr*)&socketStruct.socketAddress,
           socketStruct.socketAddressLength) < 0) {
    throw FailureSocketConnectingException(socketStruct.ipAddress,
                                           socketStruct.port);
  }
}

void closeSocket(OSSocket& socketStruct) {
  close(socketStruct.socketFD);
  close(socketStruct.newSocketFD);
}

void setAddress(const std::string& address, unsigned port,
                OSSocket& socketStruct) {
  socketStruct.ipAddress = address;
  socketStruct.port = port;
  socketStruct.socketAddressLength = sizeof(socketStruct);

  socketStruct.socketAddress.sin_family = _TCPIP_V4_DOMAIN;
  socketStruct.socketAddress.sin_port = htons(port);
  socketStruct.socketAddress.sin_addr.s_addr = inet_addr(address.c_str());
}

void startListen(OSSocket& socketStruct) {
  if (listen(socketStruct.socketFD, _MAX_SOCKET_CONNECTIONS) < 0) {
    throw FailureSocketListeningException("Failed to listen to socket");
  }

  LOG_DEBUG(fmt::format("Listening to ADDR:{} PORT:{}",
                        inet_ntoa(socketStruct.socketAddress.sin_addr),
                        ntohs(socketStruct.socketAddress.sin_port)));
}

void acceptConnection(OSSocket& socketStruct) {
  socketStruct.newSocketFD =
      accept(socketStruct.socketFD, (sockaddr*)(&socketStruct.socketAddress),
             (socklen_t*)(&socketStruct.socketAddressLength));

  if (socketStruct.newSocketFD < 0) {
    throw FailureSocketAcceptConnectionException(
        fmt::format("Server failed to accept incoming connection from ADDR:{} "
                    "PORT:{}",
                    inet_ntoa(socketStruct.socketAddress.sin_addr),
                    ntohs(socketStruct.socketAddress.sin_port)));
  }
  LOG_DEBUG(fmt::format("Server connected to ADDR:{} PORT:{}",
                        socketStruct.ipAddress, socketStruct.port));
}

void receiveBytes(OSSocket& socketStruct, char* buffer) {
  auto bytesReceived = read(socketStruct.newSocketFD, buffer, _BUFFER_SIZE);
  if (bytesReceived < 0) {
    throw FailureSocketReadingException(
        "Failed to read bytes from client socket connection");
  }
  LOG_DEBUG(fmt::format("Server has received {} bytes as Request from client.",
                        bytesReceived));
}

void sendMessage(OSSocket& socketStruct, const std::string& message) {
  auto bytesSent =
      write(socketStruct.newSocketFD, message.c_str(), message.size());
  if (bytesSent != message.size()) {
    throw FailureSocketWritingException(
        "Failed to write bytes to client socket connection");
  }
  LOG_DEBUG(
      fmt::format("Server has responded client with {} bytes", bytesSent));
}
#endif

}  // namespace

struct TcpServer::Implementation {
  OSSocket osSocket;
  std::array<char, _BUFFER_SIZE> readBuffer{0};
};

TcpServer::TcpServer(const std::string& ipAddress, unsigned port)
    : _pImpl(std::make_unique<Implementation>()) {
  setAddress(ipAddress, port, _pImpl->osSocket);
  startSocket(_pImpl->osSocket);
}

TcpServer::~TcpServer() noexcept { closeSocket(_pImpl->osSocket); }

namespace {
std::string buildHttpResponse(const std::string& message) {
  const std::string pageTitle = "PAGE TITLE";

  auto htmlFileContent = fmt::format(
      "<!DOCTYPE html><html lang=\"en\"><body><h1> {} </h1><p> Hello from your "
      "Server :) The message is {} </p></body></html>",
      pageTitle, message);
  return fmt::format(
      "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: {} \n\n{}",
      htmlFileContent.size(), htmlFileContent);
}
}  // namespace

void TcpServer::listen() {
  startListen(_pImpl->osSocket);

  auto listenLoop = [&]() {
    while (true) {
      acceptConnection(_pImpl->osSocket);

      receiveBytes(_pImpl->osSocket, _pImpl->readBuffer.data());

      sendMessage(_pImpl->osSocket, buildHttpResponse("Hello, Client!!!"));

      closeSocket(_pImpl->osSocket);
    }
  };

  listenLoop();
}

FailureSocketCreationException::FailureSocketCreationException(
    const std::string& excMsg)
    : std::runtime_error(excMsg) {}

FailureSocketConnectingException::FailureSocketConnectingException(
    const std::string& ipAddress, unsigned port)
    : std::runtime_error(
          fmt::format("Failed to connect socket to address {} and port {}",
                      ipAddress, port)) {}

FailureSocketListeningException::FailureSocketListeningException(
    const std::string& excMsg)
    : std::runtime_error(excMsg) {}

FailureSocketAcceptConnectionException::FailureSocketAcceptConnectionException(
    const std::string& excMsg)
    : std::runtime_error(excMsg) {}

FailureSocketReadingException::FailureSocketReadingException(
    const std::string& excMsg)
    : std::runtime_error(excMsg) {}

FailureSocketWritingException::FailureSocketWritingException(
    const std::string& excMsg)
    : std::runtime_error(excMsg) {}

}  // namespace cpp17Play