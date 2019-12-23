#include "Chat.h"

Chat_Receiv::Chat_Receiv(manun::function_map& map, QObject* parent)
  : QObject(parent)
  , mMap(map)
{
  mMap.add(mChatFunc);
}

Chat_Receiv::~Chat_Receiv() { mMap.remove(mChatFunc); }

void Chat_Receiv::chat(std::string message) { emit chat(QString(message.c_str())); }

Chat_Send::Chat_Send(Socket& sock, QObject* parent)
  : QObject(parent)
  , mSocket(sock)
{}

void Chat_Send::chat(std::string message)
{
  mSocket.send(manun::convert::func::to_string(mChatFunc.name(), message));
}

void Chat_Send::chat(const QString& message) { chat(message.toStdString()); }
