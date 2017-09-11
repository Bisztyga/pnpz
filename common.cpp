#include "common.h"

int Common::getSize(const char *dir)
{
  struct dirent* direntStruct;
  DIR* direntDirectory = opendir(dir);
  int counter = 0;
  if (!(NULL == direntDirectory)) {
    while (direntStruct = readdir(direntDirectory)) {
      if ('.' != direntStruct->d_name[0]) counter++;
      }
  }
  return counter;
}

int Common::getLenght(const char *dir)
{
  int counter = 0;
  while (NULL != dir[counter]) {
    counter++;
  }
  return counter;
}

Common::Common()
{

}
char* Common::contatenate(const char *_str1,const char *_str2 , int _lengthResult)
{
  char *_fullPath = ( char* ) malloc( _lengthResult + 1 );
  if (NULL==_fullPath) printf("malloc failed");
  _fullPath[_lengthResult]='\0';
  const char* _usingPointer=_str1;
  int counter = 0;
  for (int i=0; i<_lengthResult; i++) {
    if (NULL == _usingPointer[counter]) {
      _usingPointer=_str2;
      counter=0;
    }
    _fullPath[i]=_usingPointer[counter];
    counter++;
  }
  return _fullPath;
}

int Common::lookForFiles(const char *dir, char **&dirList)
{
  int size = getSize(dir);
  dirList = (char**) malloc(sizeof(char*) * size);

  struct dirent* direntStruct;
  DIR* direntDirectory = opendir(dir);
  int counter = 0;
  if (!(NULL == direntDirectory)) {
    while (direntStruct = readdir(direntDirectory)) {
      if ('.' != direntStruct->d_name[0]) {
        dirList[counter] = (char*) malloc(sizeof(char) * (1 + getLenght(direntStruct->d_name)));
        strcpy(dirList[counter], direntStruct->d_name);
        //qDebug()<<dirList[counter];
        counter++;
      }
    }
  }
  return size;
}

