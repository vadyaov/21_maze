#ifndef RENDERAREA_H_
#define RENDERAREA_H_

#include <QWidget>
#include <QPen>

#include "../controller/controller.h"

class RenderArea : public QWidget {
  Q_OBJECT

  public:
    explicit RenderArea(maze::Controller& controller, QWidget* parent = nullptr);

  public slots:
    void BrowseClicked();
    void GenerateClicked();

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    maze::Controller ctr_;
    QPen pen;
};

#endif // RENDERAREA_H_
