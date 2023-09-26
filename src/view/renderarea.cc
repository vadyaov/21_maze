#include "renderarea.h"

#include <cmath>
#include <iostream>

#include <QPainter>
#include <QFileDialog>

RenderArea::RenderArea(QWidget* parent) : QWidget(parent), ctr_() {
  pen.setWidth(2);

  setBackgroundRole(QPalette::Midlight);
  setAutoFillBackground(true);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setFixedSize(500, 500);
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
  QPainter painter(this);
  painter.setPen(pen);

  std::size_t sz = std::sqrt(ctr_.Size());

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
    painter.setPen(Qt::black);
}

void RenderArea::BrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Open .txt maze"), // leak QFileDialog
      "./../examples/", tr("Text files (*.txt)"));
  std::cout << "filename: " << filename.toStdString()<< std::endl;
  try {
    ctr_.ReadMaze(filename.toStdString());
    update();
  } catch (const std::invalid_argument& e) {
    // some actions on invalid file
  }
}

void RenderArea::GenerateClicked() {
  ctr_.GenMaze(15);
  update();
}

void RenderArea::FindSolutionClicked() {
  float ceil_size = 504.0f / std::sqrt(ctr_.Size());

  int row1 = point1.y() / ceil_size;
  int col1 = point1.x() / ceil_size;

  int row2 = point2.y() / ceil_size;
  int col2 = point2.x() / ceil_size;

  std::cout << "Point1 : " << row1 << " " << col1 << std::endl;
  std::cout << "Point2 : " << row2 << " " << col2 << std::endl;

  /* ctr_.FindSolution(row1 col1 row2 col2) */
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
  QPoint p = event->pos();
  int x = p.x(), y = p.y();

  if (event->button() == Qt::LeftButton) {
    HandleLeftMouseEvent(x, y);
    update();
  } else if (event->button() == Qt::RightButton) {
    HandleRightMouseEvent(x, y);
    update();
  }

}

void RenderArea::HandleLeftMouseEvent(int x, int y) {
  if (!point1.isNull() && !point2.isNull()) {
    static bool first_print = true;

    if (first_print) {
      point1 = QPointF(x, y);
      first_print = false;
    } else {
      point2 = QPointF(x, y);
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
