#include "asyncinotify.h"
#include <QDebug>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )



char *AsyncInotify::getFullPath( int _wd, char *_fileName)
{
  int index = getProperIndex(_wd);
  int _sizeOfDir;
  int _sizeOfName=strlen( _fileName );
  _sizeOfDir=strlen(listOfPaths[index].directory );
  char* _fullPath;
  char* _helpingPath;
  qDebug()<<"1";
  if ('/' == listOfPaths[index].directory[_sizeOfDir]) {
    _sizeOfDir++;
    _helpingPath = Common::contatenate(listOfPaths[index].directory, "/", _sizeOfDir);
  }

  qDebug()<<"2";
  _helpingPath = (char*) malloc(sizeof(char*) * _sizeOfDir + 1);
  strcpy(_helpingPath, listOfPaths[index].directory);
  _sizeOfDir +=_sizeOfName;

  qDebug()<<"3";
  _fullPath = Common::contatenate(_helpingPath, _fileName, _sizeOfDir );
  delete _helpingPath;
  qDebug()<<"Full path is"<<_fullPath;
  return _fullPath;
}

void AsyncInotify::initializeDirectories(char *mainPath)
{
  startList(mainPath);
  char** listOfFolders;
  int numberOfFolders = Common::lookForFiles(mainPath, listOfFolders);
  for (int i=0; i<numberOfFolders; i++) {
    qDebug()<<"I've found file:"<<listOfFolders[i];
    char* properFolder = Common::contatenate(mainPath, listOfFolders[i], Common::getLenght(listOfFolders[i]) + Common::getLenght(mainPath));
    addSimpleDirectory(properFolder);
    free (properFolder);
  }
}

void AsyncInotify::startList(char *mainPath)
{
    listOfPaths = (rememberPath*) malloc(2);
    fileDescriptor = inotify_init(); //get file description (handle)
    if ( fileDescriptor < 0 ) {
      perror( "inotify_init" );
    }
    listOfPaths[0].watchDescriptor = inotify_add_watch(fileDescriptor,
                                                         mainPath,
                                                         IN_CREATE);
    listOfPaths[0].directory = mainPath;
    listOfPaths[1].watchDescriptor=-1; //dump object, if you see it, it means end of list
}
void AsyncInotify::addSimpleDirectory(char *_directory)
{
  int dumpObjectIndex = getListSize();
  int updatedSize = dumpObjectIndex + 2;
  listOfPaths = (rememberPath*) realloc(listOfPaths, updatedSize * sizeof(rememberPath));
  ++dumpObjectIndex;
  listOfPaths[dumpObjectIndex].watchDescriptor = -1;
  int lastObject = dumpObjectIndex-1;
  listOfPaths[lastObject].watchDescriptor = inotify_add_watch(fileDescriptor,
                                                             _directory,
                                                             IN_CREATE |IN_DELETE);
  listOfPaths[lastObject].directory = _directory;
}

void AsyncInotify::removeDirectory(int _wd)
{
  int index = getProperIndex (_wd);
  inotify_rm_watch( fileDescriptor, listOfPaths[index].watchDescriptor );
  listOfPaths[index].directory="";
  listOfPaths[index].watchDescriptor=-2;
}

void AsyncInotify::listenForEvent()
{
  int length, i;
  char buffer[BUF_LEN];
  char *_path;
  int mainDirectory = 0;
  while(1) {
    length = read( fileDescriptor, buffer, BUF_LEN );
    if ( length < 0 ) {
      perror( "read" );
    }
    i = 0;
    while ( i < length ) {
      struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
      if (event->len) {
        if (listOfPaths[0].watchDescriptor == event->wd) mainDirectory = 1;
        else mainDirectory = 0;
        _path=getFullPath( event->wd, event->name );
        if ( event->mask & IN_CREATE ) {
          if ( (event->mask & IN_ISDIR) && 1 == mainDirectory) {
            qDebug()<<"Inot: dir"<<_path<<"has been created";
            emit inotify( _path, DIRECTORY_CREATED );
            addSimpleDirectory(_path);
            printf( "The directory %s was created.\n", _path );
          } else if ( !(event->mask & IN_ISDIR) && 0 == mainDirectory){
            emit inotify( _path, FILE_CREATED );
            printf( "The file %s was created.\n", _path );
          }
        } else if ( (event->mask & IN_DELETE) && !(event->mask & IN_ISDIR) && 0 == mainDirectory ) {
            emit inotify( _path, FILE_DELETED );
            printf( "The directory %s was deleted.\n", _path );
        }
      }
      i += EVENT_SIZE + event->len;
    }
  }
}
int AsyncInotify::getListSize()
{
  int i=0;
  do {
    if (-1 == listOfPaths[i].watchDescriptor) {
      return i;
    }
    i++;
  }
  while (true);
}
int AsyncInotify::getProperIndex(int _wd)
{
  int dumpObjectIndex = getListSize();
  int i = 0;
  while (true){
    if (dumpObjectIndex == i){
      return -1;
    }
    if (_wd == listOfPaths[i].watchDescriptor) return i;
    i++;
  }
}
AsyncInotify::AsyncInotify(char *mainDir, QObject *parent) : QThread(parent)
{
  initializeDirectories(mainDir);
}
void AsyncInotify::run() {
  setbuf(stdout, NULL); //eazy print
  listenForEvent();
}
AsyncInotify::~AsyncInotify()
{
  //TODO DESTRUCTOR
  //Not urgent since it is called only when app is shutting down - allocated memory is freed anyway;
  inotify_rm_watch( fileDescriptor, listOfPaths[0].watchDescriptor );
  QThread::wait(1500);
  qDebug()<<"destructor1";
  close( fileDescriptor );
  qDebug()<<"destructor2";
  QThread::wait(1500);
  qDebug()<<"destructed";
}

