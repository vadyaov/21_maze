#include "renderarea.h"

#include <cmath>
#include <iostream>

#include <QPainter>
#include <QPainterPath>
#include <QFileDialog>

RenderArea::RenderArea(QWidget* parent) : QWidget(parent) {
  setBackgroundRole(QPalette::Midlight);
  setAutoFillBackground(true);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setFixedSize(500, 500);
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
  QPainter painter(this);
  QPainterPath painterpath;
  painter.setPen(QPen(Qt::black, 2));

  std::size_t sz = ctr_.Size();

  if (sz) {
    painter.drawLine(QPoint(1, 1), QPoint(1, 499));
    painter.drawLine(QPoint(1, 1), QPoint(499, 1));
  }

  float length = 498.0f / sz;

  for (std::size_t i = 0; i < sz; ++i)
    for (std::size_t j = 0; j < sz; ++j) {
      float x = 1.0f + length * (j + 1);
      float y = 1.0f + length * i;

      QPointF point1(x, y);
      QPointF point2(point1 + QPoint(0.0f, length));

      QPointF point3(y, x);
      QPointF point4(point3 + QPoint(length, 0.0f));

      if (ctr_.At(i, j).IsRight())
        painter.drawLine(point1, point2);

      if (ctr_.At(j, i).IsDown())
        painter.drawLine(point3, point4);
    }

  if (!point1.isNull()) {
    painter.setPen(Qt::red);
    painter.drawEllipse(point1, 3, 3);
  }

  if (!point2.isNull()) {
    painter.setPen(Qt::blue);
    painter.drawEllipse(point2, 3, 3);
  }

  if (!solution.empty()) {
    painterpath.moveTo(point2);
    for (const auto& point : solution)
      painterpath.lineTo(point);

    painterpath.lineTo(point1);
    painter.drawPath(painterpath);
  }
}

void RenderArea::BrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Open .txt maze"), // leak QFileDialog
      "./../examples/", tr("Text files (*.txt)"));
  std::cout << "filename: " << filename.toStdString()<< std::endl;
  try {
    ctr_.ReadMaze(filename.toStdString());
    point1 = point2 = {0, 0};
    solution.clear();
    update();
  } catch (const std::invalid_argument& e) {
    // some actions on invalid file
  }
}

void RenderArea::GenerateClicked() {
  ctr_.GenMaze(15);
  point1 = point2 = {0, 0};
  solution.clear();
  update();
}


std::pair<int, int> RenderArea::ToCeilCoord(int x, int y) {
  float ceil_size = 504.0f / ctr_.Size();

  int row = y / ceil_size;
  int col = x / ceil_size;

  return {row, col};
}

void RenderArea::FindSolutionClicked() {
  solution.clear();
  std::pair<int, int> pt1 = ToCeilCoord(point1.x(), point1.y());
  std::pair<int, int> pt2 = ToCeilCoord(point2.x(), point2.y());

  const auto solution_ceils = ctr_.FindSolution(pt1, pt2);
  solution.reserve(solution_ceils.size());

  // using transform algo from STL

  /* std::transform(solution_ceils.cbegin(), solution_ceils.cend(), */
  /*     std::back_inserter(solution), [this](const std::pair<int, int>& coord) { */
  /*     return FindCenterPos(coord); }); */

  // simple understandable way of transforming
  for (const auto& coordinate : solution_ceils)
    solution.push_back(FindCenterPos(coordinate));

  update();
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
  if (!ctr_.Size()) return; // stop handling events if no maze on board

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

void RenderArea::HandleLeftMouseEvent(int x, int y) {
  if (!point1.isNull() && !point2.isNull()) {

    static bool first_print = true;

  /* IDK WHY but center alignment of doesn't work for the first two points after BrowseClicked */
    if (first_print) {
      /* without center alignment */
      /* point1 = QPointF(x, y); */

      /* with center alignment */
      point1 = FindCenterPos(ToCeilCoord(x, y));
      first_print = false;
    } else {
      /* without center alignment */
      /* point2 = QPointF(x, y); */

      /* with center alignment */
      point2 = FindCenterPos(ToCeilCoord(x, y));
      first_print = true;
    }

  } else if (!point1.isNull())
    point2 = QPointF(x, y);
  else
    point1 = QPointF(x, y);
}

void RenderArea::HandleRightMouseEvent(int x, int y) {
  if (IsPointNear(point1, x, y)) {
    point1.setX(0);
    point1.setY(0);
  } else if (IsPointNear(point2, x, y)) {
    point2.setX(0);
    point2.setY(0);
  }
}

bool RenderArea::IsPointNear(const QPointF& point, int x, int y) const {
  return (x >= point.x() - 5 && x <= point.x() + 5) &&
         (y >= point.y() - 5 && y <= point.y() + 5);
}

QPointF RenderArea::FindCenterPos(const std::pair<int, int>& coord) {
  const std::size_t sz = ctr_.Size();
  const float ceil_sz = 500.0f / sz; // mb 504

  float x = ceil_sz / 2.0f + coord.second * ceil_sz;
  float y = ceil_sz / 2.0f + coord.first * ceil_sz;

  return QPointF(x, y);
}
