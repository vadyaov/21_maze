#ifndef MAZEWINDOW_H_
#define MAZEWINDOW_H_

#include <QWidget>

#include "./../other/button.h"
#include "MazeRenderArea.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
class QComboBox;
QT_END_NAMESPACE

/**
 * @class MazeWindow
 * @brief The main window for displaying and interacting with mazes.
 *
 * The `MazeWindow` class represents the main window for displaying and
 * interacting with mazes. It provides functionality for opening, generating,
 * finding paths, and saving mazes.
 */
class MazeWindow : public QWidget {
  Q_OBJECT

 public:
  /**
   * @brief Constructor for the MazeWindow class.
   */
  MazeWindow();

  /**
   * @brief Returns the preferred size of the MazeWindow.
   *
   * @return The preferred size as a QSize.
   */
  QSize sizeHint() const override;

  /**
   * @brief Gets the selected maze size.
   *
   * @return The selected maze size.
   */
  int GetSize() const;

  /**
   * @brief Gets the selected solution color.
   *
   * @return The index of the selected solution color.
   */
  int SolutionColor() const;

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
  MazeRenderArea *render_area_; /**< The rendering area for the maze. */
  QSpinBox *size_box;           /**< Spin box for selecting maze size. */
  QComboBox *color_box;         /**< Combo box for selecting solution color. */
};

#endif  // MAZEWINDOW_H_
