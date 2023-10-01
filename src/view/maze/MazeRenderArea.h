#ifndef MAZERENDERAREA_H_
#define MAZERENDERAREA_H_

#include "./../BaseRender.h"
#include "../../controller/MazeController.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QMouseEvent;
QT_END_NAMESPACE

class MazeRenderArea : public BaseRenderArea {
  Q_OBJECT

  public:
    explicit MazeRenderArea(QWidget* parent = nullptr);

  public slots:
    void BrowseClicked() override;
    void GenerateClicked() override;
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

#endif // MAZERENDERAREA_H_
