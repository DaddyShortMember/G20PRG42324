#ifndef LOGGER_H_
#define LOGGER_H_
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Requisitos de logger:
//	1) Escribir dato de actualizacion
//	2) No sobre-escribir datos
//	3) Registrar fecha
//	4) Escribir que dato, quien, y cuando.
void logOpen(sqlite3 *db);
void logStart(sqlite3 *db, char* user);
void logAppendDB(sqlite3 *db, char* statement, int result); //Pone en fichero exactamente cada movimiento hecho a B.D.
void logEnd(sqlite3 *db, char* user);
void logExit(sqlite3 *db);

#endif /* LOGGER_H_ */
