#include "events.h"
#include "ui_events.h"

Events::Events(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Events)
{
    ui->setupUi(this);
}

Events::~Events()
{
    delete ui;
}
