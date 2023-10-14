#ifndef MAZEWINDOW_H_
#define MAZEWINDOW_H_

#include <QWidget>

#include "MazeRenderArea.h"
#include "./../other/button.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
class QComboBox;
QT_END_NAMESPACE

class MazeWindow : public QWidget {
  Q_OBJECT

  public:
    MazeWindow();

    QSize sizeHint() const override;
    int GetSize() const;
    int SolutionColor() const;

  private:
    MazeRenderArea* render_area_;

    Button *CreateButton(const QString &text, const char *member);

    QSpinBox *size_box;
    QComboBox *color_box;
};

#endif // MAZEWINDOW_H_
