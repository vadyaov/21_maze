#include "MazeRenderArea.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <cmath>

#include "MazeWindow.h"

MazeRenderArea::MazeRenderArea(QWidget* parent) : BaseRenderArea(parent) {}

void MazeRenderArea::paintEvent(QPaintEvent* /* event */) {
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2));

  DrawMaze(painter);
  DrawSolution(painter);
  DrawPoints(painter);
}

void MazeRenderArea::BrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open .txt maze"), "./examples/", tr("Text files (*.txt)"));
  try {
    ctr_.ReadMaze(filename.toStdString());
    point1 = point2 = {0, 0};
    solution.clear();
    update();
  } catch (...) {
    // do nothing
  }
}

void MazeRenderArea::GenerateClicked() {
  MazeWindow* sender = qobject_cast<MazeWindow*>(parentWidget());
  if (sender) {
    ctr_.GenMaze(sender->GetSize());
    point1 = point2 = {0, 0};
    solution.clear();
    update();
  }
}

void MazeRenderArea::FindSolutionClicked() {
  if (point1.isNull() || point2.isNull()) return;

  solution.clear();

  std::pair<int, int> pt1 = ToCeilCoord(point1.x(), point1.y());
  std::pair<int, int> pt2 = ToCeilCoord(point2.x(), point2.y());

  try {
    const auto solution_ceils = ctr_.FindSolution(pt1, pt2);
    solution.reserve(solution_ceils.size());

    // using transform algo from STL

    /* std::transform(solution_ceils.cbegin(), solution_ceils.cend(), */
    /*     std::back_inserter(solution), [this](const std::pair<int, int>&
     * coord) { */
    /*     return FindCenterPos(coord); }); */

    // simple understandable way of transforming
    for (const auto& coordinate : solution_ceils)
      solution.push_back(FindCenterPos(coordinate));

    update();
  } catch (...) {
    // do nothing
  }
}

void MazeRenderArea::SaveClicked() { ctr_.Save(); }

void MazeRenderArea::mousePressEvent(QMouseEvent* event) {
  if (!ctr_.Size()) return;

  QPoint p = event->pos();

  if (event->button() == Qt::LeftButton) {
    HandleLeftMouseEvent(p.x(), p.y());
    solution.clear();
    update();
  } else if (event->button() == Qt::RightButton) {
    HandleRightMouseEvent(p.x(), p.y());
    solution.clear();
    update();
  }
}
