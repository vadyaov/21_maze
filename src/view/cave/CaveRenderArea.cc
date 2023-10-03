#include "CaveRenderArea.h"

#include <QPainter>
#include <QFileDialog>

#include <QSpinBox>

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
  ctr_.InitializeCave(20, 0.5);
  /* CaveWindow* parent = qobject_cast<CaveWindow*>(parentWidget()); */
  /* ctr_.MakeNextGen(parent->GetLifeLimit(), parent->GetDeathLimit()); */
  update();
}
