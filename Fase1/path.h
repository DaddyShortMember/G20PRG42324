#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef PATH_H_
#define PATH_H_

typedef struct{
	int id;
    int initialstop;
    int finalstop;
}Path; //X Bytes, malloc necesario para arrays

Path getPath(sqlite3 *db, int id);
Path creaPath(int initialStop, int finalStop);
void anyadirPath(sqlite3 *db, Path Path);

int pathcrtrscr(sqlite3 *db);

void visualizarCaminos(sqlite3 *db);
void imprimirCaminos(sqlite3 *db);

#endif