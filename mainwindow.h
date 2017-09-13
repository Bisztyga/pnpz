#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <getidbox.h>
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
private slots:
  void on_pushButton_clicked();
private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
