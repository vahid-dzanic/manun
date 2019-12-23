#pragma once

#include "IEndpoint.h"
#include "Socket.h"

class Server : public IEndpoint
{
public:
  Server();
  Socket* listen(std::size_t port);

private:
  boost::asio::io_service mIO;
};
