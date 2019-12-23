#pragma once

#include "SineProtocol.h"

#include <QWidget>

namespace Ui {
class SineViewer;
}

class SineViewer : public QWidget, public SineProtocol
{
  Q_OBJECT

public:
  explicit SineViewer(manun::function_map& map, QWidget* parent = nullptr);
  ~SineViewer() override;

  // impl SineProtocol
  void data(float value) override;

signals:
  void data(const QString& value);
  void data(int value);

private:
  Ui::SineViewer* ui;
  manun::function_map& mMap;
};
