#ifndef CAVERENDERAREA_H_
#define CAVERENDERAREA_H_

#include "./../BaseRender.h"
#include "../../controller/CaveController.h"

#include <QTimer>

QT_BEGIN_NAMESPACE
class QPainter;
/* class QMouseEvent; */
QT_END_NAMESPACE

class CaveRenderArea : public BaseRenderArea {
  Q_OBJECT

  public:
    explicit CaveRenderArea(QWidget* parent = nullptr);

  public slots:
    void BrowseClicked() override;
    void GenerateClicked() override;
    void SimulationClicked();
    void TimerRoutine();

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    cave::Controller ctr_;
    QTimer *timer;
};

#endif // CAVERENDERAREA_H_
