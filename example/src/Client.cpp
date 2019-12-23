#include "Client.h"

Client::Client() { mIO.run(); }

Socket* Client::connect(const std::string& ip, std::size_t port)
{
  boost::asio::ip::tcp::socket* sock = new boost::asio::ip::tcp::socket(mIO);
  boost::asio::ip::tcp::resolver resolver(mIO);
  boost::asio::ip::tcp::resolver::query query(ip, std::to_string(port));
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  boost::system::error_code ec;
  boost::asio::connect(*sock, iterator, ec);
  if (!ec)
  {
    return new Socket(sock);
  }
  assert(false);
  return nullptr;
}
