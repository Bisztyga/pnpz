#ifndef ASYNCINOTIFY_H
#define ASYNCINOTIFY_H

#include <QThread>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <iostream>
#include <unistd.h>


#define FILE_CREATED 0
#define FILE_DELETED 1
#define FILE_RENAMED_FROM 2
#define FILE_RENAMED_TO 3
#define DIRECTORY_CREATED 10
#define DIRECTORY_DELETED 11
#define DIRECTORY_RENAMED_FROM 12
#define DIRECTORY_RENAMED_TO 13

struct rememberPath{
  int watchDescriptor;
  char *directory;
  int fileDescriptor;
};

class AsyncInotify : public QThread
{
  static char *contatenate( char *_str1, char *_str2, int _lengthResult);
  static char *getFullPath(int _wdID, char* _fileName);
  Q_OBJECT
public:
  explicit AsyncInotify(QObject *parent = 0);
  ~AsyncInotify();
  void run();
signals:
  void inotify(char *fullDirectory, int action, char *secondDirectory = NULL );
public slots:
};

#endif // ASYNCINOTIFY_H
