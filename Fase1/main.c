#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "user.h"
//#include "path.h"
//#include "route.h"
//#include "stop.h"
//#include "bus.h"
//#include "sqlite3.h"
#include "logger.h"

int lgscr(sqlite3* db); //menu de inicio de sesion
int menuAd(void); //menu principal
int menuEm(void); //menu principal
int usrscr(sqlite3* db);//menu de visualizacion/modificacion sobre: usuarios

int tripscr(sqlite3* db);//menu de visualizacion/modificacion sobre: viajes (rutas)
int busscr(sqlite3* db);//menu de visualizacion/modificacion sobre: buses

int routescr(sqlite3* db);//menu de visualizacion/modificacion sobre: rutas
int pathscr(sqlite3* db);//menu de visualizacion/modificacion sobre: caminos
int stopscr(sqlite3* db);//menu de visualizacion/modificacion sobre: paradas

 //TODO:
 //*Programar.

int main(void)
{
	int mmn = 1; //Return de Main Menu
	int lg; //Return de Log-in Screen
	int usr; // Return de sub-menus
	int usi; //User Input
	sqlite3 *db;
	sqlite3_open("DB.db", &db);
	logOpen(db);
	lg = lgscr(db);
	if(lg == 1){
		while(mmn != 0){
		mmn = menuAd();
		usi = 1;
		switch(mmn){
		case 0: system("CLS");
				logExit(db);
				break;
		case 1: while(usi != 0){
			usi = usrscr(db);
		}
				break;
		default: system("CLS");
				printf("Opcion Invalida\nHas logrado salir de una funcion de manera inadecuada...\nPresiona cualquier tecla para volver a acceder al menu principal\n");
				getch();
		}
			
		}
	}else if(lg == 2){
		while(mmn != 0){
		mmn = menuEm();
		usi = 1;
		switch(mmn){
		case 0: system("CLS");
				logExit(db);
				break;
		case 1: while(usi != 0){
				usi = tripscr(db);
		}
				break;
		case 2: while(usi != 0){
				usi = routescr(db);
		}
				break;
		default: system("CLS");
				printf("Opcion Invalida\nHas logrado salir de una funcion de manera inadecuada...\nPresiona cualquier tecla para volver a acceder al menu principal\n");
				getch();
		}
			
		}
	}
	else{
		sqlite3_close(db);
		exit(0);
	}
	
}

int lgscr(sqlite3* db){ 
	int ret;
	int qAu;
	int flg = 0;
	int flg2 = 1;
	int sec = 0;
	char* usi = malloc(sizeof(char)*30);
	char* buf = malloc(sizeof(char)*31);
	char* mail = malloc(sizeof(char)*31);
	int zz = 1;
	while(flg < 1){
	fflush(stdin);
	system("CLS");
	printf("Cliente de Admin. Local\n\n\n\n");
	printf("Introduzca su email:\n");
	fgets(buf,31,stdin);
	sscanf(buf, "%s", usi);
	qAu = exists(db, usi);
	if(qAu > 2 || qAu < 1){
		if(sec == 2){
			system("CLS");
			flg++;
			flg2--;
			ret = 0;
		}
		sec++;
		fflush(stdin);
		if(sec < 3)
			printf("Email Invalido;\nPor favor, introduzca un email valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		else
			printf("Email Invalido;\nCerrando Programa\n[PRESIONE CUALQUIER TECLA PARA SALIR]\n");
		getch();
	}
	else{
		fflush(stdin);
		strcpy(mail, usi);
		flg++;
	}
	}
	while(flg2 > 0){
	system("CLS");
	printf("Cliente de Admin. Local\n\n\n\n");
	printf("Introduzca su contrasenya:\n");
	fgets(buf,31,stdin);
	sscanf(buf, "%s", usi);
	printf("\nDEBUG: %s", usi);
	if(passCheck(db,mail,usi) == 0){
		if(sec == 2){
			system("CLS");
			flg2--;
			ret = 0;
		}
		sec++;
		fflush(stdin);
		if(sec < 3)
			printf("Contrasenya Incorrecta;\nPor favor, introduzca la contrasenya correcta\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		else
			printf("Contrasenya Incorrecta;\nCerrando Programa\n[PRESIONE CUALQUIER TECLA PARA SALIR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg2--;
		ret = qAu;
		logStart(db, mail);
	}
	}
	free(buf);
	free(usi);
	free(mail);
	return ret;
}

int menuAd(void){
	fflush(stdin);
	int ret = 1;
	int flg = 0;
	char buffer[3]; 
	int usi;
	while(flg == 0){
	system("CLS");
	printf("Cliente de Admin. Local\n");
	printf("[MENU ADMINISTRADOR]\n");
	printf("[1] Usuarios\n");
	printf("[0] Salida\n");
	printf("Introduzca su seleccion:\n");
	fflush(stdin);
	fgets(buffer,3,stdin);
	sscanf(buffer, "%d", &usi);
	switch(usi){
		case 0: system("CLS");
				ret = usi;
				flg++;
				break;
		case 1: fflush(stdin);
				system("CLS");
				ret = usi;
				flg++;
				break;
		default: system("CLS");
				printf("Opcion Invalida;\nPor favor, introduzca un numero que aparezca en el menu\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
				getch();
	}
	
	}
	return ret;
}

int menuEm(void){ 
	fflush(stdin);
	int ret = 1;
	int flg = 0;
	char buffer[3]; 
	int usi;
	while(flg == 0){
	system("CLS");
	printf("Cliente de Admin. Local\n");
	printf("[MENU EMPRESA]\n");
	printf("[1] Viajes\n");
	printf("[2] Rutas\n");
	printf("[0] Salida\n");
	printf("Introduzca su seleccion:\n");
	fflush(stdin);
	fgets(buffer,3,stdin);
	sscanf(buffer, "%d", &usi);
	switch(usi){
		case 0: system("CLS");
				ret = usi;
				flg++;
				break;
		case 1:
		case 2: fflush(stdin);
				system("CLS");
				ret = usi;
				flg++;
				break;
		default: system("CLS");
				printf("Opcion Invalida;\nPor favor, introduzca un numero que aparezca en el menu\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
				getch();
	}
	
	}
	return ret;
}

int usrscr(sqlite3* db){ 
	int ret;
	int flg = 0;
	int flg2 = 1;
	char buffer[3];
	int usi;
	while(flg == 0){
		fflush(stdin);
		system("CLS");
		flg2 = 1;
		printf("Cliente de Admin. Local\n");
		printf("[MENU USUARIOS]\n");
		printf("[1] Visualizar\n");
		printf("[2] Imprimir\n");
		printf("[3] Anyadir\n");
		printf("[4] Modificar\n");
		printf("[5] Eliminar\n");
		printf("[0] Vuelta\n");
		printf("Introduzca su seleccion:\n");
		fgets(buffer,3,stdin);
		sscanf(buffer, "%d", &usi);
		switch(usi){
			case 0:	fflush(stdin);
					system("CLS");
					ret = usi;
					flg++;
					break;
			case 1: visualizarUsuarios(db);
					break;
			case 2: imprimirUsuarios(db);
					break;
			case 3: while(flg2 == 1){
					flg2 = usrcrtscr(db);
					}
					break;
			case 4: while(flg2 == 1){
						flg2 = usmodscr(db);
					}
					break;
			case 5: while(flg2 == 1){
						flg2 = usrdltscr(db);
					}
					break;
			default: system("CLS");
					printf("Opcion Invalida;\nPor favor, introduzca un numero que aparezca en el menu\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
					getch();
		}
	}
	return ret;
}

int tripscr(sqlite3* db){}//menu de visualizacion/modificacion sobre: viajes (rutas)
int busscr(sqlite3* db){}//menu de visualizacion/modificacion sobre: buses

int routescr(sqlite3* db){}//menu de visualizacion/modificacion sobre: rutas
int pathscr(sqlite3* db){}//menu de visualizacion/modificacion sobre: caminos
int stopscr(sqlite3* db){}//menu de visualizacion/modificacion sobre: paradas