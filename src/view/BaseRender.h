#ifndef BASE_RENDER_H_
#define BASE_RENDER_H_

#include <QWidget>

/**
 * @class BaseRenderArea
 * @brief A base class for rendering graphical elements on a QWidget.
 *
 * The `BaseRenderArea` class serves as a base class for rendering graphical elements
 * on a QWidget. It provides methods for setting the background, enabling auto background
 * filling, and defining the size of the rendering area.
 */
class BaseRenderArea : public QWidget {
  Q_OBJECT

  public:
    /**
     * @brief Constructor for the BaseRenderArea class.
     *
     * @param parent The parent widget.
     */
    explicit BaseRenderArea(QWidget* parent = nullptr) : QWidget(parent) {
      setBackgroundRole(QPalette::Midlight);
      setAutoFillBackground(true);
      this->setFixedSize(500, 500);
    }

  public slots:
    /**
     * @brief Slot for handling a "Browse" button click.
     */
    virtual void BrowseClicked() = 0;

    /**
     * @brief Slot for handling a "Generate" button click.
     */
    virtual void GenerateClicked() = 0;

};

#endif // BASE_RENDER_H_
