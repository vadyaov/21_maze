#ifndef RENDERAREA_H_
#define RENDERAREA_H_

#include <QWidget>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QMouseEvent;
QT_END_NAMESPACE

class RenderArea : public QWidget {
  Q_OBJECT

  public:
    explicit RenderArea(QWidget* parent = nullptr);

  public slots:
    void BrowseClicked();
    void GenerateClicked();
    void FindSolutionClicked();

  signals:
    void ErrorOccured(const QString& msg);

  protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

  private:
    void DrawMaze(QPainter& p);
    void DrawPoints(QPainter& p);
    void DrawSolution(QPainter& p);

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
