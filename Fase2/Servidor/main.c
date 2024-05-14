#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "user.h" //Done
#include "path.h" //Done
#include "route.h" //Done
#include "stop.h" //Done
#include "bus.h" //Done
#include "sqlite3.h"
#include "trip.h" //Done
#include "logger.h"

int receiveInst(void);
//Funciones para clientes y administracion
int sendBusData(void);
int sendTripData(void);
int sendUserData(void);
//Funciones para administracion
int sendRouteData(void);
int sendStopData(void);
int sendPathData(void);
 //TODO:
 //*Programar funciones de servidor.

int main(void)
{
	return 0;
}