#include "getidbox.h"
#include "ui_getidbox.h"

GetIdBox::GetIdBox(char *mountPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetIdBox)
{
    _mount=mountPath;
    ui->setupUi(this);
}

GetIdBox::~GetIdBox()
{
    delete ui;
    parentWidget()->deleteLater();
}

void GetIdBox::on_pushButton_clicked()
{
    delete this;
}

void GetIdBox::on_pushButton_2_clicked()
{
    if (!(NULL == ui->lineEdit->text())){
        char* text = (char*) malloc(sizeof(char) * (ui->lineEdit->text().size() + 1));
        strcpy(text, ui->lineEdit->text().toStdString().c_str());
        Summary* sum = new Summary(text, _mount, this);
        sum->show();
        this->hide();
    }
}
