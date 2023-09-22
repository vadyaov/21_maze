#ifndef RENDERAREA_H_
#define RENDERAREA_H_

#include <QWidget>
#include <QPen>
#include <QBrush>

#include "../controller/controller.h"

class RenderArea : public QWidget {
  Q_OBJECT

  public:
    explicit RenderArea(maze::Controller& controller, QWidget* parent = nullptr);
    void ReadMazeFromFile(const QString&);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    maze::Controller ctr_;
    QPen pen;
};

#endif // RENDERAREA_H_
