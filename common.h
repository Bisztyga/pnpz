#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <dirent.h>
#include <QDebug>

class Common
{
public:
  Common();
  static int getLenght(const char* dir);
  static int lookForFiles(const char* dir, char **&dirList);
  static int getSize(const char* dir);
  //Contatenates 2 strings. It takes care of allocking memory for new pointer
  //and keeps strings in arguments untouched
  static char *contatenate(const char *_str1,const char *_str2, int _lengthResult);
};

#endif // COMMON_H
