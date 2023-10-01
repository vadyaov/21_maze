#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QTabWidget>
#include "./maze/mazewindow.h"
#include "./cave/cavewindow.h"

class MainWindow : public QTabWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr) : QTabWidget(parent) {
      MazeWindow *maze_window = new MazeWindow;
      CaveWindow *cave_window = new CaveWindow;
      addTab(maze_window, QString("Maze"));
      addTab(cave_window, QString("Cave"));

      setWindowTitle(tr("Maze & Cave"));
    }
    /* virtual ~MainWindow() {} */
};

#endif // MAINWINDOW_H_
