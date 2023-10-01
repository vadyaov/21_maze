#ifndef CAVERENDERAREA_H_
#define CAVERENDERAREA_H_

#include "./../base_render.h"
#include "../../controller/CaveController.h"

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

  signals:
    void ErrorOccured(const QString& msg);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    cave::Controller ctr_;
};

#endif // CAVERENDERAREA_H_
