#include "asyncinotify.h"
#include <QDebug>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )


char * file_path = "/home/bisztyga/Desktop/aaa";
rememberPath* listOfPaths;
int fd;//TODO merge into struct
char *AsyncInotify::getFullPath(rememberPath *listOfPaths, int _size, int _wdID, char *_fileName)
{
  int _sizeOfDir;
  int _sizeOfName=strlen( _fileName );
  if ( _wdID < _size && _wdID >=0 ) _sizeOfDir=strlen(listOfPaths[_wdID].directory );
  else return "{";
  char *_fullPath = ( char* ) malloc( _sizeOfDir + _sizeOfName + 1 );
  strcat( _fullPath, "/") ;
  strcat( _fullPath, _fileName );
  return _fullPath;
}

AsyncInotify::AsyncInotify(QObject *parent) :
    QThread(parent)
{
}

void AsyncInotify::run() {
  qDebug()<<"run";
  setbuf(stdout, NULL); //eazy print
  std::string fileName;
  std::cout <<"start"<< std::endl;
  int length, i;
  int sizeOfArray=1;
  fd = inotify_init(); //get file description (handle)
  if ( fd < 0 ) {
    perror( "inotify_init" );
  }
  printf( " %f was created.\n", fd );
  listOfPaths = (rememberPath*) malloc(sizeOfArray);//toremove
  listOfPaths[0].watchDescriptor = inotify_add_watch(fd, file_path, IN_ALL_EVENTS);
  listOfPaths[0].directory = file_path;
  char buffer[BUF_LEN];
  while(1) {
    length = read( fd, buffer, BUF_LEN );
    if ( length < 0 ) {
      perror( "read" );
    }
    i = 0;
    while ( i < length ) {
      struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
      if ( event->len ) {
        fileName=event->name;
        if ( event->mask & IN_CREATE ) {
          if ( event->mask & IN_ISDIR ) {
            printf( "The directory %s was created.\n", fileName.c_str() );
          } else {
            printf( "The file %s was created.\n", fileName.c_str() );
          }
        } else if ( event->mask & IN_DELETE ) {
            if ( event->mask & IN_ISDIR ) {
              printf( "The directory %s was deleted.\n", fileName.c_str() );
            } else {
              printf( "The file %s was deleted.\n", fileName.c_str() );
            }
        } else if ( event->mask & IN_MODIFY ) {
          if ( event->mask & IN_ISDIR ) {
            printf( "The directory %s was modified.\n", fileName.c_str() );
          } else {
            printf( "The file %s was modified.\n", fileName.c_str() );
          }
        }
      }
      i += EVENT_SIZE + event->len;
      fileName="";
    }
  }
}

AsyncInotify::~AsyncInotify()
{
    qDebug()<<"destructor";
    //TODO DESTRUCTOR
  inotify_rm_watch( fd, listOfPaths[0].watchDescriptor );
  QThread::wait(1500);
  qDebug()<<"destructor1";
  close( fd );
  qDebug()<<"destructor2";
  QThread::wait(1500);
  qDebug()<<"destructed";
}

