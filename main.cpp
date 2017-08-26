#include "mainwindow.h"
#include <QApplication>

#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <asyncinotify.h>



int main(int argc, char *argv[])
{

    char *s="hello";
    printf("Get length of string -> %d\n", strlen(s));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    AsyncInotify *asyncInotify = new AsyncInotify;
    asyncInotify->setObjectName("my thread");
    asyncInotify->start();

    return a.exec();
}


