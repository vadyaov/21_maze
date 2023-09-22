#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>

#include "renderarea.h"
#include "button.h"


class Window : public QWidget {
  Q_OBJECT

  public:
    Window();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    private slots:
      void BrowseClicked();

  private:
    Button *CreateButton(const QString &text, const char *member);

    RenderArea* render_area_;

};

#endif // WINDOW_H_
