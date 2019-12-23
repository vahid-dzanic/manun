#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <string>
#include <thread>

class Socket
{
public:
  constexpr static std::size_t max_length = 512; //[characters] (size_of(char) == 1 byte)
  using receiver_function_t = std::function<void(const std::string&)>;

  Socket(boost::asio::ip::tcp::socket* sock);
  virtual ~Socket();

  void setup(receiver_function_t receiver_function);
  void send(const std::string& data);

  void register_log(std::function<void(const std::string&)> log_observer);

private:
  void receive();

  std::thread* mReceiverThread;
  std::string mLocalBuffer;
  std::uintmax_t mLastMessage;

  boost::asio::ip::tcp::socket* mSocket;
  receiver_function_t mReceiverFunction;

  std::function<void(const std::string&)> mLogObserver;
};
