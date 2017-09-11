#include "summary.h"
#include "ui_summary.h"
#include "QDebug"
Summary::Summary(char* id, char* mountPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Summary)
{
    AsyncInotify *asyncInotify = new AsyncInotify(mountPath);
    asyncInotify->setObjectName("my thread");
    asyncInotify->start();
    connect( asyncInotify,
             SIGNAL(inotify(char*,int)),
             this,
             SLOT(InotifyReceived(char*,int)));

    userId=id;
    ui->setupUi(this);
    QString data=id;
    ui->label->setText(data);
    this->mountPath=mountPath;
    refresh();
}

void Summary::InotifyReceived(char *fullDirectory, int action)
{
  qDebug()<<"inotify";
  refresh();
  //printf("File :\"%s\" has changed.\n", fullDirectory);
}

Summary::~Summary()
{
    delete ui;
}

void Summary::refresh()
{
  positive = 0;
  negative = 0;
  qDebug()<<"starts refreshing";
  char** listOfFolders;
  int mountPathSize = Common::getLenght(mountPath);
  int numberOfFolders = Common::lookForFiles(mountPath, listOfFolders);
  qDebug()<<"We have "<<numberOfFolders<< "folders";
  for (int i=0; i<numberOfFolders; i++){
    int folderSize = Common::getLenght(listOfFolders[i]);
    int dirSize = folderSize + mountPathSize;
    char* folder = Common::contatenate(mountPath, listOfFolders[i], dirSize);
    char** listOfFiles;
    int numberOfFiles = Common::lookForFiles(folder, listOfFiles);
    qDebug()<<"Folder "<<folder<<" has "<<numberOfFiles<< " files";
    for (int j=0; j<numberOfFiles; j++) {
      char* properSubfolder = Common::contatenate(folder, "/", dirSize+1);
      char* properFile = Common::contatenate(properSubfolder, listOfFiles[j], Common::getLenght(listOfFiles[j]) + dirSize + 1);
      free(properSubfolder);
      qDebug()<<"file: "<<properFile;
      readFile(properFile);
      free(properFile);
      free(listOfFiles[j]);
    }
    free(folder);
    free(listOfFiles);
  }
  for (int i = 0; i<numberOfFolders; i++) {
    free(listOfFolders[i]);
  }
  free(listOfFolders);
  QString pos = QString::number(positive);
  ui->label_6->setText(pos);
  QString neg = QString::number(negative);
  ui->label_7->setText(neg);
  QString diff = QString::number(positive - negative);
  ui->label_8->setText(diff);
}

void Summary::readFile(const char *dir)
{
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  stream = fopen(dir, "r");
  if (stream == NULL)
    return;
  int counter=0;
  while ((read = getline(&line, &len, stream)) != -1 && 3 != counter) {
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }
    if ((0 == counter) && ((strcmp(line, userId))))  return;
    if (1 == counter) positive = positive + atof(line);
    if (2 == counter) negative = negative + atof(line);
    counter++;
  }
  free(line);
  fclose(stream);
 }
