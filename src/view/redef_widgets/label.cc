#include "label.h"

#include <QFont>
#include <QPainter>
#include <QPaintEvent>

#include <iostream>

Label::Label(const QString& text, QWidget* parent) : QLabel(parent) {
  setBackgroundRole(QPalette::Mid);
  setAutoFillBackground(true);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  setAlignment(Qt::AlignCenter);
  setStyleSheet("color: shadow;");

  QFont font("Arial", 16);
  setFont(font);
  setText(text);
}

QSize Label::sizeHint() const {
  return QSize(490, 40);
}

void Label::HandleError(const QString& msg) {
  setText(msg);
}
