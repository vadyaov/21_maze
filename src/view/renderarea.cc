#include "renderarea.h"

#include <cmath>
#include <iostream>
#include <QPainter>

/*
 * ВАЖНЫЙ МОМЕНТ. 
 * нужно помнить и понимать как меняется толщина линии:
 *  низ и право - вовнутрь, верх и лево - наружу (в случае Rect)
 *
 * Лабиринт состоит из ячеек со стенками, нужно, зная число будущих ячеек лабиринта,
 * заранее зарезервировать место для стенок (т.к. стенки тоже имеют толщину).
 * По сути только они же и будут орисовываться.
 * 
 * По идее будет два прохода: сначала отрисуются горизонтальные стены, потом вертикальные.
 * Только пока непонятно по каким координатам рисовать, да еще так чтобы это было грамотно и удобно
 */

RenderArea::RenderArea(QWidget* parent) : QWidget(parent) {
  QPen pen;
  pen.setWidth(2);
  pen.setBrush(Qt::black);
  SetPen(pen);

  setBackgroundRole(QPalette::Midlight);
  setAutoFillBackground(true);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setFixedSize(500, 500);
}

void RenderArea::SetPen(const QPen& pen) {
  this->pen = pen;
  update();
}

void RenderArea::SetBrush(const QBrush& brush) {
  this->brush = brush;
  update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
  QPainter painter(this);

  QPen pen1;
  pen1.setWidth(2);
  painter.setPen(pen);
  painter.drawLine(QPoint(1, 1), QPoint(1, 499));
  painter.drawLine(QPoint(1, 1), QPoint(499, 1));

  int size = 2;
  int pixels = 498;
  float wall_length = static_cast<float>(pixels) / size;
  std::cout << "wall_length = " << wall_length << std::endl;

  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j) {
      float x = 1.0f + wall_length * (j + 1);
      float y = 1.0f + wall_length * i;

      QPointF point1(x, y),
              point2(point1 + QPoint(0.0f, wall_length)),
              point3(y, x),
              point4(point3 + QPoint(wall_length, 0.0f));

      QLineF v_line(point1, point2);
      QLineF h_line(point3, point4);

      painter.drawLine(v_line);
      painter.drawLine(h_line);
    }

}
