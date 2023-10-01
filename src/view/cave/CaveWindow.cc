#include "CaveWindow.h"

#include <QGridLayout>
#include <QVBoxLayout>

CaveWindow::CaveWindow() : render_area_{new CaveRenderArea(this)} {
  Button *browse_button = CreateButton(tr("Browse"), SLOT(BrowseClicked()));
  /* Button *generate_button = CreateButton(tr("Generate"), SLOT(GenerateClicked())); */
  /* Button *findsol_button = CreateButton(tr("Find path"), SLOT(FindSolutionClicked())); */

  Label *err_label = Label::CreateLabel(tr("HELLO!"));
  connect(render_area_, &CaveRenderArea::ErrorOccured, err_label, &Label::HandleError);

  QGridLayout *main_layout = new QGridLayout;
  QVBoxLayout *buttons_layout = new QVBoxLayout;

  main_layout->addWidget(render_area_, 0, 0, 2, 1);
  main_layout->addWidget(err_label, 2, 0, 1, 1, Qt::AlignCenter);

  buttons_layout->addWidget(browse_button);
  /* buttons_layout->addWidget(generate_button); */
  /* buttons_layout->addWidget(findsol_button); */

  main_layout->addLayout(buttons_layout, 0, 2);

  setLayout(main_layout);

  setFixedSize(750, 580);
}

QSize CaveWindow::sizeHint() const {
  return QSize(600, 500);
}

Button* CaveWindow::CreateButton(const QString &text, const char *member) {
  Button* button = new Button(text);
  connect(button, SIGNAL(clicked()), render_area_, member);
  return button;
}
