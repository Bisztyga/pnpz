#include "mainwindow.h"
#include <QApplication>

#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <asyncinotify.h>
#include <common.h>

int main(int argc, char *argv[])
{
  char** test;
  int k=Common::lookForFiles("/home/bisztyga/", test);

  for (int i=0; i<k ; i++)
  {
      qDebug()<<test[i];
}
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}


