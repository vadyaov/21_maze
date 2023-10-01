#ifndef LABEL_H_
#define LABEL_H_

#include <QLabel>

class Label : public QLabel {
  Q_OBJECT

  public:
    explicit Label(const QString& text, QWidget *parent = nullptr);

    QSize sizeHint() const override;

    static Label* CreateLabel(const QString& text) {
      Label* label = new Label(text);
      return label;
    }

  public slots:
    void HandleError(const QString& msg);

};

#endif // LABEL_H_
