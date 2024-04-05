#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef TICKET_H_
#define TICKET_H_

typedef struct{
	int id;
	char name[30];
}Ticket; //X Bytes, malloc necesario para arrays

Ticket getTicket(sqlite3 *db, int id);
Ticket creaTicket(int id, char* name);
void anyadirTicket(sqlite3 *db, Ticket Ticket);

#endif