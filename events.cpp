#include "events.h"
#include "ui_events.h"

Events::Events(const char* mountPath, QWidget *parent) : QDialog(parent), ui(new Ui::Events)
{
  ui->setupUi(this);
  this->mountPath = mountPath;
  char** folders;
  int numberOfFolders = Common::lookForFiles(mountPath, folders);
  for (int i=0; i<numberOfFolders; i++) {
    const char* properFolder = Common::contatenate(mountPath, folders[i], Common::getLenght(mountPath) + Common::getLenght(folders[i]));
    QString stringified = QString::fromStdString(properFolder);
    ui->comboBox->addItem(stringified);
    free((void*) properFolder);
  }
  for (int i=0; i<numberOfFolders; i++) free(folders[i]);
  free(folders);
}

Events::~Events()
{
  delete ui;
}

void Events::on_comboBox_currentIndexChanged(const QString &arg1)
{
  ui->comboBox_2->clear();
  char* folder = (char*) malloc(sizeof(char*) * (ui->comboBox->currentText().length() + 1));
  strcpy (folder, ui->comboBox->currentText().toStdString().c_str());
  qDebug()<<"1 In folder" << ui->comboBox->currentText();
  qDebug()<<"3 In folder"<<folder;
  char** files;
  int numberOfFiles = Common::lookForFiles(folder, files);
  for (int i=0; i<numberOfFiles; i++) {
    char* helpingFile = Common::contatenate(folder, "/", Common::getLenght(folder)+1);
    char* properFile = Common::contatenate(helpingFile, files[i], Common::getLenght(folder) + Common::getLenght(files[i]) + 1);
    free(helpingFile);
    QString stringified = QString::fromStdString(properFile);
    ui->comboBox_2->addItem(stringified);
    qDebug()<<"file:"<<properFile<<"should be in combo box";
    free(properFile);
  }
}

void Events::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char* file = (char*) malloc(sizeof(char*) * (Common::getLenght(ui->comboBox_2->currentText().toStdString().c_str()) + 1));
  strcpy(file, ui->comboBox_2->currentText().toStdString().c_str());
  stream = fopen(file, "r");
  if (stream == NULL)
    return;
  int counter=0;
  while ((read = getline(&line, &len, stream)) != -1 && 3 != counter) {
    if (1 == counter) ui->doubleSpinBox->setValue(atof(line));
    if (2 == counter) ui->doubleSpinBox_2->setValue(atof(line));
    counter++;
  }
  free(line);
  fclose(stream);
  free(file);
}

void Events::on_pushButton_clicked()
{
  /*char* file = (char*) malloc(sizeof(char*) * (Common::getLenght(ui->comboBox_2->currentText().toStdString().c_str()) + 1));
  strcpy(file, ui->comboBox_2->currentText().toStdString().c_str());
  FILE *stream;
  char *name = NULL;
  size_t len = 0;
  ssize_t read;
  stream = fopen(file, "r");
  if (stream == NULL)
    return;
  read = getline(&name, &len, stream);
  fclose(stream);
  stream = fopen(file, "w+");
  fwrite(name, sizeof(char*), Common::getLenght(name), stream);
  free(name);
  free(file);*/
}
