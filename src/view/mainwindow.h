#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QTabWidget>
#include "./maze/mazewindow.h"

class MainWindow : public QTabWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr) : QTabWidget(parent) {
      MazeWindow *maze_window = new MazeWindow;
      addTab(maze_window, QString("Maze"));

      setWindowTitle(tr("Maze & Cave"));
    }
    /* virtual ~MainWindow() {} */
};

#endif // MAINWINDOW_H_
