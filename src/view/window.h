#ifndef WINDOW_H_
#define WINDOW_H_

#include <QWidget>

#include "renderarea.h"
#include "button.h"
#include "label.h"


class Window : public QWidget {
  Q_OBJECT

  public:
    Window();

    QSize sizeHint() const override;

  private:
    RenderArea* render_area_;

    Button *CreateButton(const QString &text, const char *member);
    Label *CreateLabel(const QString &text);

};

#endif // WINDOW_H_
