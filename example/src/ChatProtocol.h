#pragma once

#include <manun/includes>
#include <string>

class ChatProtocol
{
public:
  ChatProtocol()
    : mChatFunc(stdex_create(&ChatProtocol::chat, this))
  {}
  virtual ~ChatProtocol() = default;

  virtual void chat(std::string message) = 0;

protected:
  stdex::function<void(std::string)> mChatFunc;
};
