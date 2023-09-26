#include "window.h"
#include "renderarea.h"

#include <QGridLayout>

Window::Window() : render_area_{new RenderArea(this)} {
  Button *browse_button = CreateButton(tr("Browse"), SLOT(BrowseClicked()));
  Button *generate_button = CreateButton(tr("Generate"), SLOT(GenerateClicked()));
  Button *findsol_button = CreateButton(tr("Find path"), SLOT(FindSolutionClicked()));

  QGridLayout *main_layout = new QGridLayout;

  main_layout->addWidget(render_area_, 0, 0, 2, 1);
  main_layout->addWidget(browse_button, 0, 1, 1, 1, Qt::AlignTop);
  main_layout->addWidget(generate_button, 1, 1, 1, 1, Qt::AlignTop);
  main_layout->addWidget(findsol_button, 2, 1, 1, 1, Qt::AlignTop);

  setLayout(main_layout);

  setWindowTitle(tr("Maze & Cave"));
}

QSize Window::sizeHint() const {
  return QSize(600, 500);
}

QSize Window::minimumSizeHint() const {
  return QSize(500, 500);
}

Button* Window::CreateButton(const QString &text, const char *member) {
  Button* button = new Button(text);
  connect(button, SIGNAL(clicked()), render_area_, member);
  return button;
}
