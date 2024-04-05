#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef TRIP_H_
#define TRIP_H_

typedef struct{
	int id;
	char name[30];
}Trip; //X Bytes, malloc necesario para arrays

Trip getTrip(sqlite3 *db, int id);
Trip creaTrip(int id, char* name);
void anyadirTrip(sqlite3 *db, Trip Trip);

#endif