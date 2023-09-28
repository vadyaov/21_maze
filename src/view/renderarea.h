#ifndef RENDERAREA_H_
#define RENDERAREA_H_

#include <QWidget>
#include <QPen>
#include <QMouseEvent>

#include "../controller/controller.h"

class RenderArea : public QWidget {
  Q_OBJECT

  public:
    explicit RenderArea(QWidget* parent = nullptr);

  public slots:
    void BrowseClicked();
    void GenerateClicked();
    void FindSolutionClicked();

  protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

  private:
    void HandleLeftMouseEvent(int x, int y);
    void HandleRightMouseEvent(int x, int y);
    bool IsPointNear(const QPointF& point, int x, int y) const;
    QPointF FindCenterPos(const std::pair<int, int>& coord);
    std::pair<int, int> ToCeilCoord(int x, int y);

  private:
    maze::Controller ctr_;

    QPointF point1;
    QPointF point2;
    std::vector<QPointF> solution;
};

#endif // RENDERAREA_H_
