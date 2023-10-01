#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QTabWidget>
#include "window.h"

class MainWindow : public QTabWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr) : QTabWidget(parent) {
      Window *maze_window = new Window;
      addTab(maze_window, QString("Maze"));

      setWindowTitle(tr("Maze & Cave"));
    }
    /* virtual ~MainWindow() {} */
};

#endif // MAINWINDOW_H_
