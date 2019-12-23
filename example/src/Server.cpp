#include "Server.h"

Server::Server() { mIO.run(); }

Socket* Server::listen(std::size_t port)
{
  boost::asio::ip::tcp::socket* sock = new boost::asio::ip::tcp::socket(mIO);
  boost::asio::ip::tcp::endpoint server(boost::asio::ip::tcp::v4(), static_cast<std::uint16_t>(port));
  boost::asio::ip::tcp::acceptor acceptor(mIO, server);
  boost::system::error_code ec;
  acceptor.accept(*sock, server, ec);
  if (!ec)
  {
    return new Socket(sock);
  }
  assert(false);
  return nullptr;
}
