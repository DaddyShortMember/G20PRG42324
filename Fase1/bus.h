#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef BUS_H_
#define BUS_H_

typedef struct{
	int id;
	char license[10];
    int seats;
}Bus; //X Bytes, malloc necesario para arrays

Bus getBus(sqlite3 *db, int id);
Bus creaBus(int id, char* license, int seats);
void anyadirBus(sqlite3 *db, Bus bus);

#endif