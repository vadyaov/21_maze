#ifndef RENDERAREA_H_
#define RENDERAREA_H_

#include <QWidget>
#include <QPen>
#include <QBrush>

class RenderArea : public QWidget {
  Q_OBJECT

  public:
    explicit RenderArea(QWidget* parent = nullptr);

  public slots:
    void SetPen(const QPen& pen);
    void SetBrush(const QBrush& brush);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    QPen pen;
    QBrush brush;
};

#endif // RENDERAREA_H_
