#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
  int returncode = 0;
  if (argc != 1)
  {
    bool server = false;
    if (std::string(argv[1]) == "server")
    {
      server = true;
    }
    else if (std::string(argv[1]) == "client")
    {
      server = false;
    }
    else
    {
      std::cerr << "define first argument \"client\" or \"server\"" << std::endl;
      return 1;
    }
    QApplication a(argc, argv);
    MainWindow w(server);
    w.show();
    returncode = a.exec();
  }
  return returncode;
}
