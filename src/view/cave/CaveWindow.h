#ifndef CAVEWINDOW_H_
#define CAVEWINDOW_H_

#include <QWidget>

#include "CaveRenderArea.h"

#include "./../redef_widgets/button.h"
#include "./../redef_widgets/label.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
class QRadioButton;
QT_END_NAMESPACE

class CaveWindow : public QWidget {
  Q_OBJECT

  public:
    CaveWindow();

    QSize sizeHint() const override;

    int GetLifeLimit() const;
    int GetDeathLimit() const;
    double GetInitChance() const;
    int GetSize() const;
    int GetDelta() const;
    int GetSteps() const;
    bool IsAuto() const;

  private:
    CaveRenderArea* render_area_;

    Button *CreateButton(const QString &text, const char *member);

    QSpinBox *life_box;
    QSpinBox *death_box;
    QSpinBox *init_chance_box;
    QSpinBox *size_box;

    QRadioButton *auto_, *manually_;
    QSpinBox *delta_box;
    QSpinBox *steps_box;
};

#endif // CAVEWINDOW_H_

