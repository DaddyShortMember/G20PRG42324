#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef STOP_H_
#define STOP_H_

typedef struct{
	int id;
	char name[30];
}Stop; //X Bytes, malloc necesario para arrays

Stop getStop(sqlite3 *db, int id);
Stop creaStop(int id, char* name);
void anyadirStop(sqlite3 *db, Stop stop);

#endif