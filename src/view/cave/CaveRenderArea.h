#ifndef CAVERENDERAREA_H_
#define CAVERENDERAREA_H_

#include "./../BaseRender.h"
#include "../../controller/CaveController.h"

#include <QTimer>

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

/**
 * @class CaveRenderArea
 * @brief A rendering area for displaying and simulating caves.
 *
 * The `CaveRenderArea` class provides a rendering area for displaying and simulating caves.
 * It handles the painting of the cave's cells and implements functionality for opening,
 * generating, and simulating caves. This class is designed for use within the `CaveWindow`.
 */
class CaveRenderArea : public BaseRenderArea {
  Q_OBJECT

  public:
    /**
     * @brief Constructor for the CaveRenderArea class.
     * @param parent The parent widget.
     */
    explicit CaveRenderArea(QWidget* parent = nullptr);

  public slots:
    /**
     * @brief Slot to handle the "Open" button click event.
     */
    void BrowseClicked() override;

    /**
     * @brief Slot to handle the "Generate" button click event.
     */
    void GenerateClicked() override;

    /**
     * @brief Slot to handle the "Simulate" button click event.
     */
    void SimulationClicked();

    /**
     * @brief Slot to handle the timer routine for simulating cave generation.
     */
    void TimerRoutine();

  protected:
    /**
     * @brief Paint event handler for rendering the cave cells.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

  private:
    cave::Controller ctr_; /**< The controller for cave simulation. */
    QTimer *timer; /**< The timer for automatic simulation. */
};

#endif // CAVERENDERAREA_H_
