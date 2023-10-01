#ifndef CAVEWINDOW_H_
#define CAVEWINDOW_H_

#include <QWidget>

#include "caverenderarea.h"

#include "./../redef_widgets/button.h"
#include "./../redef_widgets/label.h"


class CaveWindow : public QWidget {
  Q_OBJECT

  public:
    CaveWindow();

    QSize sizeHint() const override;

  private:
    CaveRenderArea* render_area_;

    Button *CreateButton(const QString &text, const char *member);
};

#endif // CAVEWINDOW_H_

