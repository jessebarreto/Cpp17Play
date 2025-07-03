#pragma once

#include <memory>
#include <stdexcept>

namespace cpp17Play {

class TcpServer {
  struct Implementation;
  std::unique_ptr<Implementation> _pImpl;

 public:
  TcpServer(const std::string& ipAddress, unsigned port);
  ~TcpServer() noexcept;

  void listen();
};

class FailureSocketCreationException : public std::runtime_error {
 public:
  explicit FailureSocketCreationException(const std::string& excMsg);
};

class FailureSocketConnectingException : public std::runtime_error {
 public:
  FailureSocketConnectingException(const std::string& ipAddress, unsigned port);
};

class FailureSocketListeningException : public std::runtime_error {
 public:
  explicit FailureSocketListeningException(const std::string& excMsg);
};

class FailureSocketAcceptConnectionException : public std::runtime_error {
 public:
  explicit FailureSocketAcceptConnectionException(const std::string& excMsg);
};

class FailureSocketReadingException : public std::runtime_error {
 public:
  explicit FailureSocketReadingException(const std::string& excMsg);
};

class FailureSocketWritingException : public std::runtime_error {
 public:
  explicit FailureSocketWritingException(const std::string& excMsg);
};

}  // namespace cpp17Play
