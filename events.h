#ifndef EVENTS_H
#define EVENTS_H

#include <QDialog>
#include <common.h>

namespace Ui {
class Events;
}

class Events : public QDialog
{
  Q_OBJECT
public:
  explicit Events(const char *mountPath, QWidget *parent = 0);
   ~Events();
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::Events *ui;
    const char* mountPath;
};

#endif // EVENTS_H
