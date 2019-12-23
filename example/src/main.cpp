#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
  int returncode = 0;
  if (argc != 1)
  {
    if (std::string(argv[1]) == "server")
    {
      QApplication a(argc, argv);
      MainWindow w(true);
      w.show();
      returncode = a.exec();
    }
    else if (std::string(argv[1]) == "client")
    {
      QApplication a(argc, argv);
      MainWindow w(false);
      w.show();
      returncode = a.exec();
    }
  }
  return returncode;
}
