#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef TRIP_H_
#define TRIP_H_

typedef struct{
	int id;
    int busid;
    int pathid;
    char etime[5];
    char atime[5];
	int price;
}Trip; //X Bytes, malloc necesario para arrays

Trip getTrip(sqlite3 *db, int id);
Trip creaTrip(int id, int busid, int pathid, char etime[5], char atime[5], int price);
void anyadirTrip(sqlite3 *db, Trip Trip);

void visualizarTrip(sqlite3 *db);
void imprimirTrip(sqlite3 *db);

#endif