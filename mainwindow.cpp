#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  AsyncInotify *asyncInotify = new AsyncInotify("/home/bisztyga/Desktop/aaa");
  asyncInotify->setObjectName("my thread");
  asyncInotify->start();
  connect( asyncInotify,
           SIGNAL(inotify(char*,int,char*)),
           this,
           SLOT(InotifyReceived(char*,int,char*)));
}

MainWindow::~MainWindow()
{
    //TODO signal for async destructor

    delete ui;
}

void MainWindow::InotifyReceived(char *fullDirectory, int action, char *secondDirectory)
{
  //qDebug()<<"EMITED!!";
  //printf("File :\"%s\" has changed.\n", fullDirectory);
}
