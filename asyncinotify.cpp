#include "asyncinotify.h"
#include <QDebug>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

char *AsyncInotify::contatenate(char *_str1, char *_str2 , int _lengthResult)
{
  char *_fullPath = ( char* ) malloc( _lengthResult + 1 );
  if (NULL==_fullPath) printf("malloc failed");
  _fullPath[_lengthResult]='\0';
  char *_usingPointer=_str1;
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

char *AsyncInotify::getFullPath( int _wd, char *_fileName)
{
  int i=0;
  do {
    if (-1 == listOfPaths[i].fileDescriptor) {
      printf("No such descriptor. Aborting");
      return "";
    }
    if (_wd == listOfPaths[i].watchDescriptor) break;
    else i++;
  }
  while(true);
  int _sizeOfDir;
  int _sizeOfName=strlen( _fileName );
  _sizeOfDir=strlen(listOfPaths[i].directory );
  char *_fullPath;
  char *_helpingPath;
  _sizeOfDir++;
  _helpingPath = contatenate(listOfPaths[i].directory, "/", _sizeOfDir);
  _sizeOfDir +=_sizeOfName;
  _fullPath = contatenate(_helpingPath, _fileName, _sizeOfDir );
  delete _helpingPath;
  return _fullPath;
}

void AsyncInotify::initializeDirectories(char *mainPath)
{
  startList(mainPath);
  //addSimpleDirectory();
}

void AsyncInotify::startList(char *mainPath)
{
    listOfPaths = (rememberPath*) malloc(2);
    listOfPaths[0].fileDescriptor = inotify_init(); //get file description (handle)
    if ( listOfPaths[0].fileDescriptor < 0 ) {
      perror( "inotify_init" );
    }
    listOfPaths[0].watchDescriptor = inotify_add_watch(listOfPaths[0].fileDescriptor,
                                                         mainPath,
                                                         IN_ALL_EVENTS);
    listOfPaths[0].directory = mainPath;
    printf ("lOP dir :%s", listOfPaths[0].directory);
    listOfPaths[1].fileDescriptor=-1; //dump object, if you see it, it means end of list
}

void AsyncInotify::addSimpleDirectory(char *_directory)
{
  qDebug()<<"/n" << _directory << "/n";
  int counter = 0;
  while (-1 == listOfPaths[counter].fileDescriptor){
    counter++;
  };
  listOfPaths = (rememberPath*) realloc(listOfPaths, ++counter * sizeof(rememberPath));
  listOfPaths[counter].fileDescriptor = -1;
  --counter;
  listOfPaths[counter].fileDescriptor = inotify_init();
  if ( listOfPaths[counter].fileDescriptor < 0 ) {
    perror( "inotify_init" );
  }
  listOfPaths[counter].watchDescriptor = inotify_add_watch(listOfPaths[counter].fileDescriptor,
                                                           _directory,
                                                           IN_ALL_EVENTS);
  listOfPaths[counter].directory = _directory;
}

void AsyncInotify::listenForEvent()
{
    int length, i;
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
          _path=getFullPath( event->wd, event->name );
          if ( event->mask & IN_CREATE ) {
            if ( event->mask & IN_ISDIR ) {
              emit inotify( _path, DIRECTORY_CREATED );
              addSimpleDirectory(_path);
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
AsyncInotify::AsyncInotify(char *mainDir, QObject *parent) :
    QThread(parent)
{
  initializeDirectories(mainDir);
}

void AsyncInotify::run() {
  setbuf(stdout, NULL); //eazy print
  listenForEvent();
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

