#include "MazeWindow.h"

#include <QGridLayout>
#include <QLabel>

MazeWindow::MazeWindow() : render_area_{new MazeRenderArea(this)} {
  Button *browse_button = CreateButton(tr("Browse"), SLOT(BrowseClicked()));
  Button *generate_button = CreateButton(tr("Generate"), SLOT(GenerateClicked()));
  Button *findsol_button = CreateButton(tr("Find path"), SLOT(FindSolutionClicked()));
  Button *save_button = CreateButton(tr("Save"), SLOT(SaveClicked()));

  size_box = new QSpinBox;
  size_box->setRange(2, 50);

  /* Label *err_label = Label::CreateLabel(tr("HELLO!")); */
  /* connect(render_area_, &MazeRenderArea::ErrorOccured, err_label, &Label::HandleError); */

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *settings_layout = new QGridLayout;

  main_layout->addWidget(render_area_, 0, 0, 2, 1);
  /* main_layout->addWidget(err_label, 2, 0, 1, 1, Qt::AlignCenter); */

  settings_layout->addWidget(browse_button, 0, 0, 1, 1);
  settings_layout->addWidget(save_button, 0, 1, 1, 1);
  settings_layout->addWidget(generate_button, 1, 0, 1, 1);
  settings_layout->addWidget(size_box, 1, 1, 1, 1);
  settings_layout->addWidget(findsol_button, 2, 0, 1, 2);

  main_layout->addLayout(settings_layout, 0, 2, 1, 1);

  setLayout(main_layout);

  /* setFixedSize(750, 580); */
}

QSize MazeWindow::sizeHint() const {
  return QSize(600, 500);
}

Button* MazeWindow::CreateButton(const QString &text, const char *member) {
  Button* button = new Button(text);
  connect(button, SIGNAL(clicked()), render_area_, member);
  return button;
}

int MazeWindow::GetSize() const {
  return size_box->value();
}

