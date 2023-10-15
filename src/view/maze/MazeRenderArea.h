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
    void SaveClicked();

  protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

  private:
    void DrawMaze(QPainter&);
    void DrawPoints(QPainter&);
    void DrawSolution(QPainter&);

    void HandleLeftMouseEvent(int, int);
    void HandleRightMouseEvent(int, int);
    bool IsPointNear(const QPointF&, int, int) const;
    QPointF FindCenterPos(const std::pair<int, int>&);
    std::pair<int, int> ToCeilCoord(int, int);

  private:
    maze::Controller ctr_;

    QPointF point1;
    QPointF point2;
    std::vector<QPointF> solution;
};

#endif // MAZERENDERAREA_H_
