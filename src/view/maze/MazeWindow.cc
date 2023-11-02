#include "MazeWindow.h"

#include <QComboBox>
#include <QFont>
#include <QGridLayout>
#include <QSpinBox>

MazeWindow::MazeWindow() : render_area_{new MazeRenderArea(this)} {
  Button *browse_button = CreateButton(tr("Open"), SLOT(BrowseClicked()));
  Button *generate_button =
      CreateButton(tr("Generate"), SLOT(GenerateClicked()));
  Button *findsol_button =
      CreateButton(tr("Find path"), SLOT(FindSolutionClicked()));
  Button *save_button = CreateButton(tr("Save"), SLOT(SaveClicked()));

  size_box = new QSpinBox;
  color_box = new QComboBox;
  size_box->setRange(2, 50);

  size_box->setFixedHeight(30);
  color_box->setFixedHeight(30);
  size_box->setFixedWidth(100);
  color_box->setFixedWidth(100);

  color_box->addItem("PURPLE");
  color_box->addItem("GREEN");
  color_box->addItem("YELLOW");
  color_box->addItem("BLUE");
  connect(color_box, SIGNAL(currentIndexChanged(int)), render_area_,
          SLOT(update()));

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *settings_layout = new QGridLayout;

  main_layout->addWidget(render_area_, 0, 0, 2, 1);

  settings_layout->addWidget(browse_button, 0, 0, 1, 1);
  settings_layout->addWidget(save_button, 0, 1, 1, 1);
  settings_layout->addWidget(generate_button, 1, 0, 1, 1);
  settings_layout->addWidget(size_box, 1, 1, 1, 1);
  settings_layout->addWidget(findsol_button, 2, 0, 1, 1);
  settings_layout->addWidget(color_box, 2, 1, 1, 1);

  main_layout->addLayout(settings_layout, 0, 2, 1, 1);

  setLayout(main_layout);
}

QSize MazeWindow::sizeHint() const { return QSize(600, 500); }

Button *MazeWindow::CreateButton(const QString &text, const char *member) {
  Button *button = new Button(text);
  connect(button, SIGNAL(clicked()), render_area_, member);
  return button;
}

int MazeWindow::GetSize() const { return size_box->value(); }

int MazeWindow::SolutionColor() const { return color_box->currentIndex(); }
