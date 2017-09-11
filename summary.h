#ifndef SUMMARY_H
#define SUMMARY_H

#include <QDialog>
#include "asyncinotify.h"
#include <stdlib.h>

namespace Ui {
class Summary;
}

class Summary : public QDialog
{
  Q_OBJECT

public:
  explicit Summary(char* id, char *mountPath, QWidget *parent = 0);
  ~Summary();

private:
  double positive;
  double negative;
  void refresh();
  const char* mountPath;
  char* userId;
  Ui::Summary *ui;
  void readFile(const char* dir);

public slots:
  void InotifyReceived(char *fullDirectory, int action);
};

#endif // SUMMARY_H
