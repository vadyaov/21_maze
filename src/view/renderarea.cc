#include "renderarea.h"

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
  painter.setPen(pen);
  /* std::cout << width() << ' ' << height() << std::endl; */
  painter.drawRect(QRect(1, 1, width() - 2, height() - 2));
}
