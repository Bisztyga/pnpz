#ifndef GETIDBOX_H
#define GETIDBOX_H

#include <QDialog>
#include <summary.h>

namespace Ui {
class GetIdBox;
}

class GetIdBox : public QDialog
{
  Q_OBJECT
public:
  explicit GetIdBox(char* mountPath, QWidget *parent = 0);
  ~GetIdBox();
private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_lineEdit_editingFinished();

private:
    Ui::GetIdBox *ui;
    char* _mount;
};

#endif // GETIDBOX_H
