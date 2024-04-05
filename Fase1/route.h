#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef ROUTE_H_
#define ROUTE_H_

typedef struct{
	int id;
	int pathid;
    int currentstopid; //Parada actual
    int nextstopid; //Siguiente Parada
    int ordernumber; //Numero de orden (si es la primera, o la segunda. Esta la hago yo)
}Route; //X Bytes, malloc necesario para arrays

Route getRoute(sqlite3 *db, int id);
Route creaRoute(int id, char* name);
void anyadirRoute(sqlite3 *db, Route Route);

#endif