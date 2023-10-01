#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QTabWidget>
#include "maze/MazeWindow.h"
#include "cave/CaveWindow.h"

class MainWindow : public QTabWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr) : QTabWidget(parent) {
      MazeWindow *maze_window = new MazeWindow;
      CaveWindow *cave_window = new CaveWindow;
      addTab(maze_window, QString("Maze"));
      addTab(cave_window, QString("Cave"));

      /* setFixedSize(750, 600); */
      setWindowTitle(tr("Maze & Cave"));
    }

    QSize sizeHint() const override {
      return QSize(750, 600);
    }

};

#endif // MAINWINDOW_H_
