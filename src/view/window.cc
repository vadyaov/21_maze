#include "window.h"
#include "renderarea.h"

#include <QGridLayout>

Window::Window() {
  render_area_ = new RenderArea;

  Button *browse_button = CreateButton(tr("Browse"), SLOT(BrowseClicked()));

  QGridLayout *main_layout = new QGridLayout;

  main_layout->addWidget(render_area_, 0, 0, 2, 1);
  main_layout->addWidget(browse_button, 0, 1, 1, 1);

  main_layout->setColumnStretch(0, 0);
  main_layout->setRowStretch(0, 0);

  setLayout(main_layout);

  setWindowTitle(tr("Maze & Cave"));
}

QSize Window::sizeHint() const {
  return QSize(600, 500);
}

QSize Window::minimumSizeHint() const {
  return QSize(500, 500);
}

void Window::BrowseClicked() {
  /* static int width = 1; */
  /* QPen pen; */
  /* pen.setWidth(width); */
  /* render_area_->SetPen(pen); */
  /* width += 1; */
}

Button* Window::CreateButton(const QString &text, const char *member) {
  Button* button = new Button(text);
  connect(button, SIGNAL(clicked()), this, member);
  return button;
}
