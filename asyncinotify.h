#ifndef ASYNCINOTIFY_H
#define ASYNCINOTIFY_H

#include <QThread>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <iostream>
#include <unistd.h>
#include <common.h>

#define FILE_CREATED 0
#define FILE_DELETED 1
#define FILE_RENAMED_FROM 2
#define FILE_RENAMED_TO 3
#define DIRECTORY_CREATED 10
#define DIRECTORY_DELETED 11
#define DIRECTORY_RENAMED_FROM 12
#define DIRECTORY_RENAMED_TO 13



class AsyncInotify : public QThread
{
  struct rememberPath{
    int watchDescriptor;
    char* directory;
  };
  rememberPath* listOfPaths;
  //It is used to get full directory of changed file
  //User needs to provide ID of "listOfPaths" member and name of changed file
  char *getFullPath(int _wdID, char* _fileName);
  //Called only at program start, read all directories and sets watches;
  void initializeDirectories(char* mainPath);
  //Adds first element of list and dump object indicated its end
  void startList(char* mainPath);
  void addSimpleDirectory(char* _directory);
  //Removes watch directory. Object of struct isn't
  //
  void removeDirectory(int _wd);
  void listenForEvent();
  int getListSize();
  int getProperIndex(int _wd);
  int fileDescriptor;
  Q_OBJECT
public:
  explicit AsyncInotify(char* mainDir, QObject *parent = 0);
  ~AsyncInotify();
  void run();
signals:
  void inotify(char *fullDirectory, int action );
public slots:
};

#endif // ASYNCINOTIFY_H
