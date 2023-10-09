#include "CaveRenderArea.h"

#include <QPainter>
#include <QFileDialog>

#include <QSpinBox>

#include "CaveWindow.h"

CaveRenderArea::CaveRenderArea(QWidget* parent) : BaseRenderArea(parent), timer{new QTimer(this)} {
  connect(timer, &QTimer::timeout, this, &CaveRenderArea::TimerRoutine);
}

void CaveRenderArea::paintEvent(QPaintEvent * /* event */) {
  QPainter painter(this);
  std::size_t size = ctr_.Size();
  std::size_t ceil_size = 500.0 / size;
  
  for (std::size_t i = 0; i < size; ++i) {
    for (std::size_t j = 0; j < size; ++j) {
      float x = j * ceil_size;
      float y = i * ceil_size;

      if (ctr_.At(i, j) == true)
        painter.fillRect(x, y, ceil_size, ceil_size, Qt::black);
      else
        painter.fillRect(x, y, ceil_size, ceil_size, Qt::white);

    }
  }
}

void CaveRenderArea::BrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Open .txt cave"),
      "./examples/", tr("Text files (*.txt)"));
  QFileInfo fileinfo(filename);
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
    /* emit ErrorOccured(e.what()); */
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
    /* std::cout << "Need to handle ERROR\n"; */
    step_num = steps;
  }

}

void CaveRenderArea::SimulationClicked() {
  CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  try {
    if (parent->IsAuto()) {
      timer->setInterval(parent->GetDelta());
      timer->start();
    } else {
      ctr_.MakeNextGen(parent->GetLifeLimit(), parent->GetDeathLimit());
      update();
    }
  } catch (const std::exception& e) {
    /* emit ErrorOccured(e.what()); */
    /* std::cout << "Need to handle ERROR\n"; */
  }
}
