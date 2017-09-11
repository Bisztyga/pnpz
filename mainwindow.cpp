#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    //TODO signal for async destructor

    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    char* text = (char*) malloc(sizeof(char) * (ui->lineEdit->text().size() + 1));
    strcpy(text, ui->lineEdit->text().toStdString().c_str());

    GetIdBox* idBox = new GetIdBox(text, this);
    idBox->show();
    this->hide();
}



