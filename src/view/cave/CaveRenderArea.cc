#include "CaveRenderArea.h"

#include <QPainter>
#include <QFileDialog>

#include <QSpinBox>

#include "CaveWindow.h"

CaveRenderArea::CaveRenderArea(QWidget* parent) : BaseRenderArea(parent), timer{new QTimer(this)} {
  connect(timer, &QTimer::timeout, this, &CaveRenderArea::TimerRoutine);
}

void CaveRenderArea::paintEvent(QPaintEvent * /* event */) {
  static CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  static const QColor alive_colors[] = {Qt::black, Qt::red, Qt::blue, Qt::magenta};
  static const QColor dead_colors[] = {Qt::lightGray, Qt::darkGray, Qt::blue, Qt::darkGreen};
  const int color_1 = parent->LifeColor();
  const int color_2 = parent->DeathColor();
  QPainter painter(this);
  std::size_t size = ctr_.Size();
  std::size_t ceil_size = 500.0 / size;
  
  for (std::size_t i = 0; i < size; ++i) {
    for (std::size_t j = 0; j < size; ++j) {
      float x = j * ceil_size;
      float y = i * ceil_size;

      if (ctr_.At(i, j) == true)
        painter.fillRect(x, y, ceil_size, ceil_size, alive_colors[color_1]);
      else
        painter.fillRect(x, y, ceil_size, ceil_size, dead_colors[color_2]);

    }
  }
}

void CaveRenderArea::BrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Open .txt cave"),
      "./examples/", tr("Text files (*.txt)"));
  try {
    ctr_.ReadCave(filename.toStdString());
    /* emit ErrorOccured(fileinfo.fileName() + " loaded successfully"); */
    update();
  } catch (const std::invalid_argument& e) {
    /* emit ErrorOccured(e.what()); */
    /* std::cout << "Need to handle ERROR\n"; */
  }
}

void CaveRenderArea::GenerateClicked() {
  if (timer->isActive()) timer->stop();

  CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  try {
    ctr_.InitializeCave(parent->GetSize(), parent->GetInitChance());
    update();
  } catch (const std::exception& e) {
    /* std::cout << "Need to handle ERROR\n"; */
  }
}

void CaveRenderArea::TimerRoutine() {
  static const CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  static int step_num = 0;

  int steps = parent->GetSteps();
  if (step_num >= steps) {
    timer->stop();
    step_num = 0;
    return;
  }

  try {
    ctr_.MakeNextGen(parent->GetLifeLimit(), parent->GetDeathLimit());
    update();
    step_num++;
  } catch (const std::exception& e) {
    step_num = steps;
  }

}

void CaveRenderArea::SimulationClicked() {
  if (timer->isActive()) return; // if simulating process on --> then do nothing

  static const CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  try {
    if (parent->IsAuto()) {
      timer->setInterval(parent->GetDelta());
      timer->start();
    } else {
      ctr_.MakeNextGen(parent->GetLifeLimit(), parent->GetDeathLimit());
      update();
    }
  } catch (const std::exception& e) {
    /* std::cout << "Need to handle ERROR\n"; */
  }
}
