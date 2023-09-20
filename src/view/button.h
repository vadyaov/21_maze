#ifndef BUTTON_H_
#define BUTTON_H_

#include <QToolButton>

class Button : public QToolButton {
  Q_OBJECT

 public:
  explicit Button(const QString &text, QWidget *parent = nullptr);

  QSize sizeHint() const override;
};

#endif // BUTTON_H_
