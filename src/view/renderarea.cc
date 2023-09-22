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

RenderArea::RenderArea(maze::Controller& controller, QWidget* parent) : QWidget(parent), ctr_(controller) {
  pen.setWidth(2);
  pen.setBrush(Qt::magenta);

  setBackgroundRole(QPalette::Midlight);
  setAutoFillBackground(true);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setFixedSize(500, 500);
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
  std::size_t sz = ctr_.Size();
  if (sz > 1) {
    QPainter painter(this);
    painter.setPen(pen);
    painter.drawLine(QPoint(1, 1), QPoint(1, 499));
    painter.drawLine(QPoint(1, 1), QPoint(499, 1));

    float length = 498.0f / sz;
    /* std::cout << "length = " << length << std::endl; */

    const auto& vertical_walls = ctr_.GetVerticalWalls();
    const auto& horizontal_walls = ctr_.GetHorizontalWalls();
    for (std::size_t i = 0; i < sz; ++i)
      for (std::size_t j = 0; j < sz; ++j) {
        float x = 1.0f + length * (j + 1);
        float y = 1.0f + length * i;

        QPointF point1(x, y),
                point2(point1 + QPoint(0.0f, length)),
                point3(y, x),
                point4(point3 + QPoint(length, 0.0f));

        QLineF v_line(point1, point2);
        QLineF h_line(point3, point4);

        if (vertical_walls[i][j])
          painter.drawLine(v_line);
        if (horizontal_walls[j][i])
          painter.drawLine(h_line);
      }
  }

}

void RenderArea::ReadMazeFromFile(const QString& path) {
  ctr_.ReadMaze(path.toStdString());
  update();
}
