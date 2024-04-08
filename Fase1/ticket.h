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
	char date[30];
}Ticket; //X Bytes, malloc necesario para arrays

//Esta la dejamos para la siguiente, al no ser importante para la primera entrega (el programa es servidor local; esta ya es para el programa tal cual)

#endif