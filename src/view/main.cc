#include "mainwindow.h"

#include <QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  MainWindow tab_window;
  tab_window.show();

  return app.exec();
}
