#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QTabWidget>

#include "cave/CaveWindow.h"
#include "maze/MazeWindow.h"

/**
 * @class MainWindow
 * @brief The main application window for the Maze & Cave application.
 *
 * The `MainWindow` class represents the main application window for the Maze &
 * Cave application. It contains two tabs, one for displaying mazes and another
 * for caves.
 */
class MainWindow : public QTabWidget {
  Q_OBJECT

 public:
  /**
   * @brief Constructor for the MainWindow class.
   *
   * @param parent The parent widget.
   */
  MainWindow(QWidget *parent = nullptr) : QTabWidget(parent) {
    maze::MazeWindow *maze_window = new maze::MazeWindow;
    cave::CaveWindow *cave_window = new cave::CaveWindow;
    addTab(maze_window, QString("Maze"));
    addTab(cave_window, QString("Cave"));

    setWindowTitle(tr("Maze & Cave"));
  }

  /**
   * @brief Returns the preferred size of the main window.
   *
   * @return The preferred size of the main window as a QSize.
   */
  QSize sizeHint() const override { return QSize(1000, 550); }
};

#endif  // MAINWINDOW_H_
