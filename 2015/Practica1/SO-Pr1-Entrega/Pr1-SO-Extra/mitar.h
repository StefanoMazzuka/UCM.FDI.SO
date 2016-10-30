#ifndef _MITAR_H
#define _MITAR_H

#include <limits.h>

typedef enum{
  NONE,
  ERROR,
  CREATE,
  EXTRACT,
  LIST
} flags;

typedef struct {
  char* name;
  unsigned int size;
} stHeaderEntry;

int createTar(int nFiles, char *fileNames[], char tarName[]);
int extractTar(char tarName[]);
// Nueva funcion a ejecutar
int listTar(char tarName[]);

#endif /* _MITAR_H */
