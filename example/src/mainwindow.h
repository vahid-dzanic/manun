#pragma once

#include "Chat.h"
#include "IEndpoint.h"
#include "Socket.h"

#include <manun/includes>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(bool server, QWidget* parent = 0);
  ~MainWindow();

  void log(const std::string& data);

signals:
  void send_chat(const QString& data);
  void log_signal(const QString& data);

private slots:
  void on_send_message_clicked();
  void on_message_text_returnPressed();
  void log_slot(const QString& data);

private:
  Ui::MainWindow* ui;
  bool mServer;
  IEndpoint* mEndpoint;
  Socket* mSocket;
  manun::function_map manun_func_map;
  Chat_Send* mChatSend;
  Chat_Receiv* mChatReceiv;
};
