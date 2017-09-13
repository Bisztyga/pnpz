#ifndef GETEVENT_H
#define GETEVENT_H

#include <QDialog>

namespace Ui {
class GetEvent;
}

class GetEvent : public QDialog
{
    Q_OBJECT
public:
  explicit GetEvent(QWidget *parent = 0);
  ~GetEvent();
private:
    Ui::GetEvent *ui;
};

#endif // GETEVENT_H
