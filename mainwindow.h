#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "asyncinotify.h"
#include <stdio.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  AsyncInotify *asyncInotify;

public slots:
    void InotifyReceived(char *fullDirectory, int action, char *secondDirectory = NULL );
private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
