#include "window.h"
#include "renderarea.h"

#include "../controller/controller.h"

#include <QGridLayout>
#include <QFileDialog>

Window::Window() {
  maze::Controller controller;
  render_area_ = new RenderArea(controller);

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
  QString filename = QFileDialog::getOpenFileName(this, tr("Open .txt maze"), // leak QFileDialog
      "./../examples/", tr("Text files (*.txt)"));
  std::cout << "filename: " << filename.toStdString()<< std::endl;
  render_area_->ReadMazeFromFile(filename);
  /* render_area_->ReadMazeFromFile("/home/vadim/Projects/School21/21_maze/src/examples/maze_1.txt"); */
}

Button* Window::CreateButton(const QString &text, const char *member) {
  Button* button = new Button(text);
  connect(button, SIGNAL(clicked()), this, member);
  return button;
}
