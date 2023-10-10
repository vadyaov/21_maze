#ifndef MAZEWINDOW_H_
#define MAZEWINDOW_H_

#include <QWidget>

#include "MazeRenderArea.h"
#include "./../other/button.h"

#include <QSpinBox>

class MazeWindow : public QWidget {
  Q_OBJECT

  public:
    MazeWindow();

    QSize sizeHint() const override;
    int GetSize() const;

  private:
    MazeRenderArea* render_area_;

    Button *CreateButton(const QString &text, const char *member);

    QSpinBox* size_box;
};

#endif // MAZEWINDOW_H_
