#include "CaveWindow.h"

#include <QComboBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QVBoxLayout>

namespace cave {

CaveWindow::CaveWindow() : render_area_{new CaveRenderArea(this)} {
  Button *browse_button = CreateButton(tr("Open"), SLOT(BrowseClicked()));
  Button *generate_button =
      CreateButton(tr("Generate"), SLOT(GenerateClicked()));
  Button *simulation_button =
      CreateButton(tr("Simulate"), SLOT(SimulationClicked()));
  simulation_button->setSizePolicy(QSizePolicy::Preferred,
                                   QSizePolicy::Preferred);

  life_box = new QSpinBox;
  death_box = new QSpinBox;
  init_chance_box = new QSpinBox;
  size_box = new QSpinBox;
  color_box_0 = new QComboBox;
  color_box_1 = new QComboBox;
  connect(color_box_0, SIGNAL(currentIndexChanged(int)), render_area_,
          SLOT(update()));
  connect(color_box_1, SIGNAL(currentIndexChanged(int)), render_area_,
          SLOT(update()));

  auto_ = new QRadioButton("Auto");
  manually_ = new QRadioButton("Manually");

  delta_box = new QSpinBox;
  steps_box = new QSpinBox;

  manually_->setChecked(true);

  life_box->setRange(-1, 7);
  death_box->setRange(-1, 7);
  init_chance_box->setRange(-1, 100);
  size_box->setRange(-1, 50);
  delta_box->setRange(1, 1000);
  steps_box->setRange(1, 50);

  life_box->setSpecialValueText(tr("Life"));
  death_box->setSpecialValueText(tr("Death"));
  init_chance_box->setSpecialValueText(tr("Initial chance"));
  size_box->setSpecialValueText(tr("Size"));

  life_box->setValue(4);
  death_box->setValue(3);
  init_chance_box->setValue(48);
  size_box->setValue(50);
  delta_box->setValue(400);
  steps_box->setValue(5);

  init_chance_box->setSuffix(" %");
  delta_box->setSuffix(" ms");
  steps_box->setSuffix(" step(s)");

  color_box_0->addItem("DARK WHITE");
  color_box_0->addItem("GRAY");
  color_box_0->addItem("BLUE");
  color_box_0->addItem("GREEN");

  color_box_1->addItem("BLACK");
  color_box_1->addItem("RED");
  color_box_1->addItem("BLUE");
  color_box_1->addItem("PURPLE");

  QGridLayout *main_layout = new QGridLayout;
  QGridLayout *settings_layout = new QGridLayout;

  settings_layout->addWidget(browse_button, 0, 0, 1, 3);
  settings_layout->addWidget(generate_button, 1, 0, 1, 1);
  settings_layout->addWidget(simulation_button, 2, 0, 2, 1);
  settings_layout->addWidget(life_box, 2, 1, 1, 1);
  settings_layout->addWidget(death_box, 2, 2, 1, 1);
  settings_layout->addWidget(init_chance_box, 1, 2, 1, 1);
  settings_layout->addWidget(size_box, 1, 1, 1, 1);
  settings_layout->addWidget(auto_, 3, 1, 1, 1);
  settings_layout->addWidget(manually_, 3, 2, 1, 1);
  settings_layout->addWidget(steps_box, 4, 1, 1, 1);
  settings_layout->addWidget(delta_box, 4, 2, 1, 1);
  settings_layout->addWidget(color_box_0, 5, 1, 1, 1);
  settings_layout->addWidget(color_box_1, 5, 2, 1, 1);

  main_layout->addWidget(render_area_, 0, 0, 2, 1);

  main_layout->addLayout(settings_layout, 0, 1, 2, 3, Qt::AlignTop);

  setLayout(main_layout);
}

QSize CaveWindow::sizeHint() const { return QSize(600, 500); }

Button *CaveWindow::CreateButton(const QString &text, const char *member) {
  Button *button = new Button(text);
  connect(button, SIGNAL(clicked()), render_area_, member);
  return button;
}

int CaveWindow::GetLifeLimit() const {
  if (life_box->value() == -1) throw std::range_error("No life limit");
  return life_box->value();
}

int CaveWindow::GetDeathLimit() const {
  if (death_box->value() == -1) throw std::range_error("No death limit");
  return death_box->value();
}

double CaveWindow::GetInitChance() const {
  if (init_chance_box->value() == -1)
    throw std::range_error("No init probability");
  return static_cast<double>(init_chance_box->value() / 100.0);
}

int CaveWindow::GetSize() const {
  if (size_box->value() == -1) throw std::range_error("No size");
  return size_box->value();
}

int CaveWindow::GetDelta() const { return delta_box->value(); }

int CaveWindow::GetSteps() const { return steps_box->value(); }

bool CaveWindow::IsAuto() const { return auto_->isChecked(); }

int CaveWindow::LifeColor() const { return color_box_1->currentIndex(); }

int CaveWindow::DeathColor() const { return color_box_0->currentIndex(); }

}  // namespace cave
