#ifndef BASE_RENDER_H_
#define BASE_RENDER_H_

#include <QWidget>

class BaseRenderArea : public QWidget {
  Q_OBJECT

  public:
    explicit BaseRenderArea(QWidget* parent = nullptr) : QWidget(parent) {
      setBackgroundRole(QPalette::Midlight);
      setAutoFillBackground(true);
      /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
      this->setFixedSize(500, 500);
    }

  public slots:
    virtual void BrowseClicked() = 0;
    virtual void GenerateClicked() = 0;

};

#endif // BASE_RENDER_H_
