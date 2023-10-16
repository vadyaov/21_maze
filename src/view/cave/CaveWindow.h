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

/**
 * @class CaveWindow
 * @brief The main window for displaying and simulating caves.
 *
 * The `CaveWindow` class represents the main window for displaying and simulating caves.
 * It provides functionality for opening, generating, simulating caves, and customizing
 * various parameters such as life and death limits, initial chance, size, and colors.
 */
class CaveWindow : public QWidget {
  Q_OBJECT

  public:
    /**
     * @brief Constructor for the CaveWindow class.
     */
    CaveWindow();

    /**
     * @brief Returns the preferred size of the CaveWindow.
     *
     * @return The preferred size as a QSize.
     */
    QSize sizeHint() const override;

    /**
     * @brief Gets the selected life limit for cave simulation.
     *
     * @return The selected life limit.
     */
    int GetLifeLimit() const;

    /**
     * @brief Gets the selected death limit for cave simulation.
     *
     * @return The selected death limit.
     */
    int GetDeathLimit() const;

    /**
     * @brief Gets the selected initial chance for cave initialization.
     *
     * @return The selected initial chance as a probability (0.0 to 1.0).
     */
    double GetInitChance() const;

    /**
     * @brief Gets the selected cave size for simulation.
     *
     * @return The selected cave size.
     */
    int GetSize() const;

    /**
     * @brief Gets the selected delta value for cave simulation.
     *
     * @return The selected delta value in milliseconds.
     */
    int GetDelta() const;

    /**
     * @brief Gets the selected number of simulation steps.
     *
     * @return The selected number of simulation steps.
     */
    int GetSteps() const;

    /**
     * @brief Checks if the auto simulation mode is selected.
     *
     * @return True if auto simulation is selected, false otherwise.
     */
    bool IsAuto() const;

    /**
     * @brief Gets the selected color for representing life cells in the simulation.
     *
     * @return The index of the selected color for life cells.
     */
    int LifeColor() const;

    /**
     * @brief Gets the selected color for representing death cells in the simulation.
     *
     * @return The index of the selected color for death cells.
     */
    int DeathColor() const;

  private:
    /**
     * @brief Creates a button with the specified text and member function.
     *
     * @param text The text label for the button.
     * @param member The member function to connect the button click signal to.
     * @return A button widget.
     */
    Button *CreateButton(const QString &text, const char *member);

  private:
    CaveRenderArea* render_area_; /**< The rendering area for the cave simulation. */

    QSpinBox *life_box; /**< Spin box for selecting the life limit. */
    QSpinBox *death_box; /**< Spin box for selecting the death limit. */
    QSpinBox *init_chance_box; /**< Spin box for selecting the initial chance. */
    QSpinBox *size_box; /**< Spin box for selecting the cave size. */

    QRadioButton *auto_, *manually_; /**< Radio buttons for selecting simulation mode. */

    QSpinBox *delta_box; /**< Spin box for selecting the simulation delta value. */
    QSpinBox *steps_box; /**< Spin box for selecting the number of simulation steps. */

    QComboBox *color_box_0; /**< Combo box for selecting death cell color. */
    QComboBox *color_box_1; /**< Combo box for selecting life cell color. */
};

#endif // CAVEWINDOW_H_
