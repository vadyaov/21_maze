#ifndef MAZERENDERAREA_H_
#define MAZERENDERAREA_H_

#include "./../BaseRender.h"
#include "../../controller/MazeController.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QMouseEvent;
QT_END_NAMESPACE

/**
 * @class MazeRenderArea
 * @brief A rendering area for displaying and interacting with mazes.
 *
 * The `MazeRenderArea` class provides a rendering area for displaying mazes and allows
 * interactions such as opening, generating, and finding solutions within the maze. This
 * class is designed for use within the `MazeWindow`.
 */
class MazeRenderArea : public BaseRenderArea {
  Q_OBJECT

  public:
    /**
     * @brief Constructor for the MazeRenderArea class.
     * @param parent The parent widget.
     */
    explicit MazeRenderArea(QWidget* parent = nullptr);

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
     * @brief Slot to handle the "Find Solution" button click event.
     */
    void FindSolutionClicked();

    /**
     * @brief Slot to handle the "Save" button click event.
     */
    void SaveClicked();

  protected:
    /**
     * @brief Paint event handler for rendering the maze.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief Mouse event handler for user interaction.
     * @param event The mouse event.
     */
    void mousePressEvent(QMouseEvent* event) override;

  private:
    /**
     * @brief Draw the maze structure.
     * @param p The QPainter object for drawing.
     */
    void DrawMaze(QPainter& p);

    /**
     * @brief Draw user-selected points.
     * @param p The QPainter object for drawing.
     */
    void DrawPoints(QPainter& p);

    /**
     * @brief Draw the solution path.
     * @param p The QPainter object for drawing.
     */
    void DrawSolution(QPainter& p);

    /**
     * @brief Handle left mouse click.
     * @param x The x-coordinate of the mouse click.
     * @param y The y-coordinate of the mouse click.
     */
    void HandleLeftMouseEvent(int x, int y);

    /**
     * @brief Handle right mouse click.
     * @param x The x-coordinate of the mouse click.
     * @param y The y-coordinate of the mouse click.
     */
    void HandleRightMouseEvent(int x, int y);

    /**
     * @brief Check if a point is near a given location.
     * @param point The point to check.
     * @param x The x-coordinate to compare.
     * @param y The y-coordinate to compare.
     * @return True if the point is near the specified location, false otherwise.
     */
    bool IsPointNear(const QPointF& point, int x, int y) const;

    /**
     * @brief Calculate the center position in cell of a given coordinate.
     * @param coord The coordinate to calculate the center position for point.
     * @return The center position as a QPointF.
     */
    QPointF FindCenterPos(const std::pair<int, int>& coord);

    /**
     * @brief Convert screen coordinates to maze cell coordinates.
     * @param x The x-coordinate in screen space.
     * @param y The y-coordinate in screen space.
     * @return A pair representing the corresponding maze cell coordinates.
     */
    std::pair<int, int> ToCeilCoord(int x, int y);

  private:
    maze::Controller ctr_; /**< The controller for maze interactions. */
    QPointF point1; /**< The first selected point for interaction. */
    QPointF point2; /**< The second selected point for interaction. */
    std::vector<QPointF> solution; /**< The solution path for maze solving. */
};

#endif // MAZERENDERAREA_H_
