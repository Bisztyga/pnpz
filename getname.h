#ifndef GETNAME_H
#define GETNAME_H

#include <QDialog>

namespace Ui {
class GetName;
}

class GetName : public QDialog
{
  Q_OBJECT
public:
  explicit GetName(QWidget *parent = 0);
  ~GetName();
private:
  Ui::GetName *ui;
};

#endif // GETNAME_H
