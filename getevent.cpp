#include "getevent.h"
#include "ui_getevent.h"

GetEvent::GetEvent(QWidget *parent) : QDialog(parent), ui(new Ui::GetEvent)
{
  ui->setupUi(this);
}

GetEvent::~GetEvent()
{
  delete ui;
}
