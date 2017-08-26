#ifndef ASYNCINOTIFY_H
#define ASYNCINOTIFY_H

#include <QThread>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <iostream>
#include <unistd.h>

struct rememberPath{
  int watchDescriptor;
  char *directory;
};

class AsyncInotify : public QThread
{
  char *getFullPath(rememberPath *listOfPaths, int _size, int _wdID, char* _fileName);
  Q_OBJECT
public:
  explicit AsyncInotify(QObject *parent = 0);
  ~AsyncInotify();
  void run();
signals:
  void fileadded(char *fullDirectory);
public slots:
};

#endif // ASYNCINOTIFY_H
