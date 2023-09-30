#include "renderarea.h"

#include <cmath>
#include <iostream>

#include <QPainter>
#include <QPainterPath>
#include <QFileDialog>
#include <QMouseEvent>

RenderArea::RenderArea(QWidget* parent) : QWidget(parent) {
  setBackgroundRole(QPalette::Midlight);
  setAutoFillBackground(true);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setFixedSize(500, 500);
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2));

  DrawMaze(painter);
  DrawPoints(painter);
  DrawSolution(painter);
}

void RenderArea::BrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Open .txt maze"), // leak QFileDialog
      "./examples/", tr("Text files (*.txt)"));
  QFileInfo fileinfo(filename);
  try {
    ctr_.ReadMaze(filename.toStdString());
    point1 = point2 = {0, 0};
    solution.clear();
    emit ErrorOccured(fileinfo.fileName() + " loaded successfully");
    update();
  } catch (const std::invalid_argument& e) {
    emit ErrorOccured(e.what());
  }
}

void RenderArea::GenerateClicked() {
  int size = 10;
  ctr_.GenMaze(size);
  point1 = point2 = {0, 0};
  solution.clear();
  emit ErrorOccured("Generated " + QString::number(size) + 'x' + QString::number(size));
  update();
}

void RenderArea::FindSolutionClicked() {
  solution.clear();

  std::pair<int, int> pt1 = ToCeilCoord(point1.x(), point1.y());
  std::pair<int, int> pt2 = ToCeilCoord(point2.x(), point2.y());

  try {
    const auto solution_ceils = ctr_.FindSolution(pt1, pt2);
    solution.reserve(solution_ceils.size());

    // using transform algo from STL

    /* std::transform(solution_ceils.cbegin(), solution_ceils.cend(), */
    /*     std::back_inserter(solution), [this](const std::pair<int, int>& coord) { */
    /*     return FindCenterPos(coord); }); */

    // simple understandable way of transforming
    for (const auto& coordinate : solution_ceils)
      solution.push_back(FindCenterPos(coordinate));

    emit ErrorOccured("Solution found");
    update();
  } catch (const std::exception& e) {
    emit ErrorOccured(e.what());
  }
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
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
