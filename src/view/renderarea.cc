#include "renderarea.h"

#include <cmath>
#include <iostream>

#include <QPainter>
#include <QFileDialog>

RenderArea::RenderArea(maze::Controller& controller, QWidget* parent) : QWidget(parent), ctr_(controller) {
  pen.setWidth(2);
  pen.setBrush(Qt::black);

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
