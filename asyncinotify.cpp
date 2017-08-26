#include "asyncinotify.h"
#include <QDebug>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )


char * file_path = "/home/bisztyga/Desktop/aaa";
static rememberPath* listOfPaths;

char *AsyncInotify::contatenate(char *_str1, char *_str2 , int _lengthResult)
{
  char *_fullPath = ( char* ) malloc( _lengthResult + 1 );
  if (NULL==_fullPath) printf("malloc failed");
  _fullPath[_lengthResult]='\0';
  char *_usingPointer=_str1;
  int counter = 0;
  for (int i=0; i<_lengthResult; i++) {
    if (NULL==_usingPointer[i]) {
      _usingPointer=_str2;
      counter=0;
    }
    _fullPath[i]=_usingPointer[counter];
    counter++;
  }
  return _fullPath;
}

char *AsyncInotify::getFullPath( int _wdID, char *_fileName)
{
  int _sizeOfDir;
  int _sizeOfName=strlen( _fileName );
  _sizeOfDir=strlen(listOfPaths[_wdID].directory );
  char *_fullPath;
  char *_helpingPath;
  _sizeOfDir++;
  _helpingPath = contatenate(listOfPaths[_wdID].directory, "/", _sizeOfDir);
  _sizeOfDir +=_sizeOfName;
  _fullPath = contatenate(_helpingPath, _fileName, _sizeOfDir );
  delete _helpingPath;
  return _fullPath;
}

AsyncInotify::AsyncInotify(QObject *parent) :
    QThread(parent)
{
}

void AsyncInotify::run() {
  qDebug()<<"run";
  setbuf(stdout, NULL); //eazy print
  int length, i;
  int sizeOfArray=1;
  listOfPaths = (rememberPath*) malloc(sizeOfArray);//toremove
  listOfPaths[0].fileDescriptor = inotify_init(); //get file description (handle)
  if ( listOfPaths[0].fileDescriptor < 0 ) {
    perror( "inotify_init" );
  }
  printf( " %d was created.\n", listOfPaths[0].fileDescriptor );
  listOfPaths[0].watchDescriptor = inotify_add_watch(listOfPaths[0].fileDescriptor,
                                                     file_path,
                                                     IN_ALL_EVENTS);
  listOfPaths[0].directory = file_path;
  printf ("lOP dir :%s", listOfPaths[0].directory);
  char buffer[BUF_LEN];
  char *_path;
  while(1) {
    length = read( listOfPaths[0].fileDescriptor, buffer, BUF_LEN );
    if ( length < 0 ) {
      perror( "read" );
    }
    i = 0;
    while ( i < length ) {
      struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
      if ( event->len ) {
        _path=getFullPath( 0, event->name );
        if ( event->mask & IN_CREATE ) {
          if ( event->mask & IN_ISDIR ) {
            emit inotify( _path, DIRECTORY_CREATED );
            printf( "The directory %s was created.\n", _path );
          } else {
            emit inotify( _path, FILE_CREATED );
            printf( "The file %s was created.\n", _path );
          }
        } else if ( event->mask & IN_DELETE ) {
            if ( event->mask & IN_ISDIR ) {
              emit inotify( _path, DIRECTORY_DELETED );
              printf( "The directory %s was deleted.\n", _path );
            } else {
              emit inotify( _path, FILE_DELETED );
              printf( "The file %s was deleted.\n", _path );
            }
        }
      }
      i += EVENT_SIZE + event->len;
    }
  }
}

AsyncInotify::~AsyncInotify()
{
    qDebug()<<"destructor";
    //TODO DESTRUCTOR
  inotify_rm_watch( listOfPaths[0].fileDescriptor, listOfPaths[0].watchDescriptor );
  QThread::wait(1500);
  qDebug()<<"destructor1";
  close( listOfPaths[0].fileDescriptor );
  qDebug()<<"destructor2";
  QThread::wait(1500);
  qDebug()<<"destructed";
}

