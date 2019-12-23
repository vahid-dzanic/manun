#include "SineViewer.h"

#include "ui_SineViewer.h"

SineViewer::SineViewer(manun::function_map& map, QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::SineViewer)
  , mMap(map)
{
  ui->setupUi(this);
  mMap.add(mDataFunc);
  connect(this, SIGNAL(data(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
  connect(this, SIGNAL(data(int)), ui->dial, SLOT(setValue(int)));
  connect(this, SIGNAL(data(int)), ui->verticalSlider, SLOT(setValue(int)));
}

SineViewer::~SineViewer()
{
  delete ui;
  mMap.remove(mDataFunc);
}

void SineViewer::data(float value)
{
  emit data(QString("%1").arg(value));
  emit data(static_cast<int>(value * 100));
}
