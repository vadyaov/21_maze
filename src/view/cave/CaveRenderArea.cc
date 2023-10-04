#include "CaveRenderArea.h"

#include <QPainter>
#include <QFileDialog>

#include <QSpinBox>
#include <QTimer>

#include "CaveWindow.h"

CaveRenderArea::CaveRenderArea(QWidget* parent) : BaseRenderArea(parent) {}

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
    emit ErrorOccured(fileinfo.fileName() + " loaded successfully");
    update();
  } catch (const std::invalid_argument& e) {
    emit ErrorOccured(e.what());
  }
}

void CaveRenderArea::GenerateClicked() {
  CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  try {
    ctr_.InitializeCave(parent->GetSize(), parent->GetInitChance());
    update();
  } catch (const std::exception& e) {
    emit ErrorOccured(e.what());
  }
}

void CaveRenderArea::SimulationClicked() {
  CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  try {
    if (parent->IsAuto()) {
      /* int steps = parent->GetSteps(); */
      int delta_t = parent->GetDelta();
      QTimer *timer = new QTimer(this);
      connect(timer, &QTimer::timeout, this, &CaveRenderArea::MakeNextGen);
      timer->start(delta_t);
    } else {
      MakeNextGen();
    }
  } catch (const std::exception& e) {
    emit ErrorOccured(e.what());
  }
}

void CaveRenderArea::SaveClicked() {
  ctr_.Save();
}

void CaveRenderArea::MakeNextGen() {
  static CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget());
  ctr_.MakeNextGen(parent->GetLifeLimit(), parent->GetDeathLimit());
  update();
}
