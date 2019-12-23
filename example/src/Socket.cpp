#include "Socket.h"

#include <manun/includes>
#include <cassert>
#include <iomanip>
#include <iostream>

Socket::Socket(boost::asio::ip::tcp::socket* sock)
  : mReceiverThread(nullptr)
  , mLastMessage(0)
  , mSocket(nullptr)
{
  mSocket = sock;
  assert(mSocket != nullptr);
}

Socket::~Socket()
{
  if (mSocket != nullptr)
  {
    mSocket->close();
    delete mSocket;
    mSocket = nullptr;
  }
  if (mReceiverThread != nullptr)
  {
    if (mReceiverThread->joinable())
    {
      mReceiverThread->join();
    }
    delete mReceiverThread;
    mReceiverThread = nullptr;
  }
}

void Socket::setup(Socket::receiver_function_t receiver_function)
{
  assert(mReceiverThread == nullptr);
  mReceiverFunction = receiver_function;
  mReceiverThread = new std::thread(std::bind(&Socket::receive, this));
}

void Socket::send(const std::string& data)
{
  if (mSocket->is_open())
  {
    // 3*[0-F] 3*[0-F] ---> 6 signs
    std::size_t payloadSize = max_length - 6;
    auto msg_count =
      static_cast<std::size_t>(ceil(static_cast<double>(data.size()) / static_cast<double>(payloadSize)));
    assert(msg_count <= 0xFFF);

    std::ostringstream ossMessages;
    ossMessages << std::setfill('0') << std::setw(3) << std::hex << msg_count;

    std::string text = data;

    for (std::size_t i = 0; i < msg_count; ++i)
    {
      std::ostringstream ossCurrentMessage;
      ossCurrentMessage << std::setfill('0') << std::setw(3) << std::hex << (i + 1);

      if (text.size() > payloadSize)
      {
        boost::system::error_code ignored_error;
        boost::asio::write(
          *mSocket,
          boost::asio::buffer(ossCurrentMessage.str() + ossMessages.str() + text.substr(0, payloadSize)),
          ignored_error);
        text = text.substr(payloadSize);
      }
      else
      {
        boost::system::error_code ignored_error;
        boost::asio::write(
          *mSocket, boost::asio::buffer(ossCurrentMessage.str() + ossMessages.str() + text), ignored_error);
      }
    }
  }
}

void Socket::register_log(std::function<void(const std::string&)> log_observer) { mLogObserver = log_observer; }

void Socket::receive()
{
  std::array<char, max_length> buf;
  for (;;)
  {
    boost::system::error_code error;
    size_t len = mSocket->read_some(boost::asio::buffer(buf), error);
    if (!error)
    {
      std::string data(buf.data(), len);
      if (mLogObserver)
      {
        mLogObserver("recieved: " + data);
      }
      auto currentMessage = manun::std_type_converter::string2arithmetic<std::uint32_t>(data.substr(0, 3));
      assert(mLastMessage + 1 == currentMessage);
      mLastMessage = currentMessage;
      auto messages = manun::std_type_converter::string2arithmetic<std::uint32_t>(data.substr(3, 3));
      if (currentMessage == 1)
      {
        mLocalBuffer = data.substr(6);
      }
      else
      {
        mLocalBuffer += data.substr(6);
      }
      if (currentMessage == messages)
      {
        mLastMessage = 0;
        assert(mReceiverFunction);
        mReceiverFunction(mLocalBuffer);
      }
    }
    else
    {
      return;
    }
  }
}
