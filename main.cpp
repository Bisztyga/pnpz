#include "mainwindow.h"
#include <QApplication>

#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <asyncinotify.h>



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}


