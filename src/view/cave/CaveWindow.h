#ifndef CAVEWINDOW_H_
#define CAVEWINDOW_H_

#include <QWidget>

#include "CaveRenderArea.h"

#include "./../other/button.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
class QComboBox;
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
    int LifeColor() const;
    int DeathColor() const;

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
    QComboBox *color_box_0;
    QComboBox *color_box_1;
};

#endif // CAVEWINDOW_H_

