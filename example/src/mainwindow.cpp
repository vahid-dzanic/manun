#include "mainwindow.h"

#include "Client.h"
#include "Server.h"
#include "SineGenerator.h"
#include "SineViewer.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(bool server, QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , mServer(server)
  , mEndpoint(nullptr)
  , mSocket(nullptr)
  , mChatSend(nullptr)
  , mChatReceiv(new Chat_Receiv(manun_func_map, this))
{
  ui->setupUi(this);
  connect(mChatReceiv, SIGNAL(chat(QString)), ui->received, SLOT(append(QString)));
  connect(this, SIGNAL(log_signal(QString)), this, SLOT(log_slot(QString)));
  if (mServer)
  {
    setWindowTitle("Server");
    Server* server = new Server();
    mEndpoint = server;
    mSocket = server->listen(62266);
  }
  else
  {
    setWindowTitle("Client");
    Client* client = new Client();
    mEndpoint = client;
    mSocket = client->connect("localhost", 62266);
  }
  assert(mSocket != nullptr);
  mChatSend = new Chat_Send(*mSocket, this);
  connect(this, SIGNAL(send_chat(QString)), mChatSend, SLOT(chat(QString)));
  mSocket->setup(std::bind(&manun::function_map::execute, &manun_func_map, std::placeholders::_1));
  mSocket->register_log(std::bind(&MainWindow::log, this, std::placeholders::_1));
  if (mServer)
  {
    auto sine_w = new SineGenerator(*mSocket, ui->sine_tab);
    sine_w->setObjectName(QStringLiteral("sine_widget"));
    ui->sine_layout->addWidget(sine_w);
  }
  else
  {
    auto sine_w = new SineViewer(manun_func_map, ui->sine_tab);
    sine_w->setObjectName(QStringLiteral("sine_widget"));
    ui->sine_layout->addWidget(sine_w);
  }
  repaint();
}

MainWindow::~MainWindow()
{
  delete ui;
  ui = nullptr;

  delete mChatReceiv;
  mChatReceiv = nullptr;

  delete mChatSend;
  mChatSend = nullptr;

  delete mSocket;
  mSocket = nullptr;

  delete mEndpoint;
  mEndpoint = nullptr;
}

void MainWindow::log(const std::string& data) { emit log_signal(QString(data.c_str())); }

void MainWindow::on_send_message_clicked() { on_message_text_returnPressed(); }

void MainWindow::on_message_text_returnPressed()
{
  emit send_chat(ui->message_text->text());
  ui->message_text->clear();
}

void MainWindow::log_slot(const QString& data) { ui->logger->appendPlainText(data); }
