#pragma once

#include "ChatProtocol.h"
#include "Socket.h"

#include <manun/includes>
#include <QObject>

class Chat_Receiv : public QObject, public ChatProtocol
{
  Q_OBJECT

public:
  Chat_Receiv(manun::function_map& map, QObject* parent = nullptr);
  virtual ~Chat_Receiv() override;

  virtual void chat(std::string message) override;

signals:
  void chat(const QString& message);

private:
  manun::function_map& mMap;
};

class Chat_Send : public QObject, public ChatProtocol
{
  Q_OBJECT

public:
  Chat_Send(Socket& sock, QObject* parent = nullptr);

  virtual void chat(std::string message);

public slots:
  void chat(const QString& message);

private:
  Socket& mSocket;
};
