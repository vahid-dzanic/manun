#pragma once

#include "SineProtocol.h"
#include "Socket.h"

#include <QWidget>
#include <thread>

namespace Ui {
class SineGenerator;
}

class SineGenerator : public QWidget, public SineProtocol
{
  Q_OBJECT

public:
  explicit SineGenerator(Socket& sock, QWidget* parent = nullptr);
  ~SineGenerator() override;

  // impl SineProtocol
  void data(float value) override;

private slots:
  void on_stop_generator_clicked();
  void on_start_generator_toggled(bool checked);

private:
  void generate();

  void stopOSC();
  void startOSC();

  Ui::SineGenerator* ui;
  Socket& mSocket;
  float mNr;
  bool mRunning;
  std::thread* mOSC;
};
