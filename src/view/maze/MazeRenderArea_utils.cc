#include <QPainter>
#include <QPainterPath>

#include "MazeRenderArea.h"
#include "MazeWindow.h"

namespace maze {

void MazeRenderArea::DrawMaze(QPainter& p) {
  std::size_t sz = ctr_.Size();

  if (sz) {
    p.drawLine(QPoint(1, 1), QPoint(1, 499));
    p.drawLine(QPoint(1, 1), QPoint(499, 1));
  }

  float length = 498.0f / sz;
  for (std::size_t i = 0; i < sz; ++i) {
    for (std::size_t j = 0; j < sz; ++j) {
      float x = 1.0f + length * (j + 1);
      float y = 1.0f + length * i;

      QPointF point1(x, y);
      QPointF point2(point1 + QPoint(0.0f, length));

      QPointF point3(y, x);
      QPointF point4(point3 + QPoint(length, 0.0f));

      if (ctr_.At(i, j).right) p.drawLine(point1, point2);

      if (ctr_.At(j, i).bottm) p.drawLine(point3, point4);
    }
  }
}

void MazeRenderArea::DrawPoints(QPainter& p) {
  if (!point1.isNull()) {
    p.setPen(Qt::red);
    p.setBrush(Qt::red);
    p.drawEllipse(point1, 2, 2);
  }

  if (!point2.isNull()) {
    p.setPen(Qt::blue);
    p.setBrush(Qt::blue);
    p.drawEllipse(point2, 2, 2);
  }
}

void MazeRenderArea::DrawSolution(QPainter& p) {
  static const QColor color[] = {Qt::magenta, Qt::green, Qt::yellow, Qt::cyan};
  if (!solution.empty()) {
    MazeWindow* sender = qobject_cast<MazeWindow*>(parentWidget());
    int i = sender->SolutionColor();

    QPainterPath painterpath;

    p.setPen(color[i]);
    p.setBrush(Qt::NoBrush);

    painterpath.moveTo(point2);
    for (const auto& point : solution) painterpath.lineTo(point);
    painterpath.lineTo(point1);

    p.drawPath(painterpath);
  }
}

void MazeRenderArea::HandleLeftMouseEvent(int x, int y) {
  if (!point1.isNull() && !point2.isNull()) {
    static bool first_print = true;

    if (first_print) {
      point1 = FindCenterPos(ToCeilCoord(x, y));
      first_print = false;
    } else {
      point2 = FindCenterPos(ToCeilCoord(x, y));
      first_print = true;
    }

  } else if (!point1.isNull())
    point2 = FindCenterPos(ToCeilCoord(x, y));
  else
    point1 = FindCenterPos(ToCeilCoord(x, y));
}

void MazeRenderArea::HandleRightMouseEvent(int x, int y) {
  if (IsPointNear(point1, x, y)) {
    point1.setX(0);
    point1.setY(0);
  } else if (IsPointNear(point2, x, y)) {
    point2.setX(0);
    point2.setY(0);
  }
}

bool MazeRenderArea::IsPointNear(const QPointF& point, int x, int y) const {
  return (x >= point.x() - 5 && x <= point.x() + 5) &&
         (y >= point.y() - 5 && y <= point.y() + 5);
}

QPointF MazeRenderArea::FindCenterPos(const std::pair<int, int>& coord) {
  const std::size_t sz = ctr_.Size();
  const float ceil_sz = 500.0f / sz;

  float x = ceil_sz / 2.0f + coord.second * ceil_sz;
  float y = ceil_sz / 2.0f + coord.first * ceil_sz;

  return QPointF(x, y);
}

std::pair<int, int> MazeRenderArea::ToCeilCoord(int x, int y) {
  float ceil_size = 504.0f / ctr_.Size();

  int row = y / ceil_size;
  int col = x / ceil_size;

  return {row, col};
}

}  // namespace maze
