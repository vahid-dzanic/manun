#include "SineGenerator.h"

#include "ui_SineGenerator.h"

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

SineGenerator::SineGenerator(Socket& sock, QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::SineGenerator)
  , mSocket(sock)
  , mNr(0)
  , mRunning(false)
  , mOSC(nullptr)
{
  ui->setupUi(this);
  ui->stop_generator->setDisabled(true);
}

SineGenerator::~SineGenerator()
{
  delete ui;
  stopOSC();
}

void SineGenerator::generate()
{
  while (mRunning)
  {
    float val = std::sin(mNr);
    // std::cout << "std::sin(" << std::setprecision(3) << mNr << ") = " << std::setprecision(3) << val << "\n";
    data(val);
    mNr += ui->doubleSpinBox->value();
    std::this_thread::sleep_for(std::chrono::microseconds(ui->spinBox->value()));
  }
}

void SineGenerator::data(float value) { mSocket.send(manun::convert::func::to_string(mDataFunc.name(), value)); }

void SineGenerator::on_stop_generator_clicked()
{
  ui->start_generator->toggle();
  ui->stop_generator->setDisabled(true);
}

void SineGenerator::on_start_generator_toggled(bool checked)
{
  if (checked)
  {
    ui->stop_generator->setEnabled(true);
    ui->start_generator->setDisabled(true);

    startOSC();
  }
  else
  {
    stopOSC();
    ui->start_generator->setEnabled(true);
  }
}

void SineGenerator::stopOSC()
{
  if (mOSC != nullptr)
  {
    mRunning = false;
    if (mOSC->joinable())
    {
      mOSC->join();
    }
    delete mOSC;
    mOSC = nullptr;
  }
}

void SineGenerator::startOSC()
{
  if (mOSC == nullptr)
  {
    mRunning = true;
    mOSC = new std::thread(std::bind(&SineGenerator::generate, this));
  }
}
