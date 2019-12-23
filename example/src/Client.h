#pragma once

#include "IEndpoint.h"
#include "Socket.h"

class Client : public IEndpoint
{
public:
  Client();
  Socket* connect(const std::string& ip, std::size_t port);

private:
  boost::asio::io_service mIO;
};
