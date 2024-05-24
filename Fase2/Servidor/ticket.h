#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef TICKET_H_
#define TICKET_H_

typedef struct{
	int id;
    	int usid;
   	int tripid;
	char date[13];
}Ticket; //X Bytes, malloc necesario para arrays

Ticket getTicket(sqlite3 *db, int id);
Ticket creaTicket(int usid, int tripid, const char* date);
void anyadirTicket(sqlite3 *db, Ticket ticket);

#endif
