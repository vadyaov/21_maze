#ifndef MAZEWINDOW_H_
#define MAZEWINDOW_H_

#include <QWidget>

#include "MazeRenderArea.h"
#include "./../redef_widgets/button.h"
#include "./../redef_widgets/label.h"

class MazeWindow : public QWidget {
  Q_OBJECT

  public:
    MazeWindow();

    QSize sizeHint() const override;

  private:
    MazeRenderArea* render_area_;

    Button *CreateButton(const QString &text, const char *member);
};

#endif // MAZEWINDOW_H_
