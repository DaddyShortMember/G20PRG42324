#include "bus.h"

Bus getBus(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	Bus qBus;
	int result;
	char* query = malloc(sizeof(char)*1028);
	sprintf(query, "select * from Bus where id = %d", id);
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	if (result == SQLITE_ROW) {
		qBus.id = sqlite3_column_int(stmt, 0);
		strcpy(qBus.license,sqlite3_column_text(stmt, 3));
		qBus.seats = sqlite3_column_int(stmt, 2);
	}else{
		system("CLS");
		qBus.id = 0;
		printf("Bus no existe.");
		getch();
	}
	sqlite3_finalize(stmt);
	free(query);
	return qBus;
}

Bus creaBus(char license[10], int seats){
    Bus qBus;
    strcpy(qBus.license, license);
	qBus.seats = seats;
	return qBus;
}

void anyadirBus(sqlite3 *db, Bus bus){
    char* query = malloc(sizeof(char)*256);
	sqlite3_stmt *stmt;
	int result;
	sprintf(query, "insert into Bus (id, license, seats) values (NULL, '%s', %d)", bus.license, bus.seats);
	result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al preparar el query (INSERT)\n");
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error al introducir Bus\n");
	}else{
		printf("Bus introducido\n");
	}
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}

void eliminarBus(sqlite3 *db, int id){
	char* query =  malloc(sizeof(char)*256);
	sprintf(query, "delete from Bus where id= %d",id);
	int result;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	sqlite3_finalize(stmt);
}

//Menus
int buscrtrscr(sqlite3 *db){
    //Menu de creacion de Bus
	char* qLic = malloc(sizeof(char)*10);
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*11);
	int qSeats;
	int res = 0;
	Bus qBus;
	int flg0 = 0;
	int flg1 = 0;
	while(flg0 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Bus]\n\nIntroduzca una matricula valida\n\n");
	fgets(qBuf,11,stdin);
	sscanf(qBuf, "%s", qLic);
	if(strlen(qLic) > 10){ 
		fflush(stdin);
		printf("Matricula Invalida;\nPor favor, introduzca una matricula valida\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}else{
		fflush(stdin);
		flg0++;
	}
	}
    flg0--;
	while(flg1 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Bus]\n\nIntroduzca un numero de asientos valido\n\n");
	fgets(qBuf,10,stdin);
	sscanf(qBuf, "%d", &qSeats);
	if(qSeats < 0){ 
		fflush(stdin);
		printf("Asientos Invalidos;\nPor favor, introduzca un numero de asientos valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg1++;
	}
	}
    flg1--;
	qBus = creaBus(qLic,qSeats);
	anyadirBus(db,qBus);
	printf("[Creacion de Bus]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
	getch();
	while(flg0 == 0){
		system("CLS");
		printf("Quiere anyadir otro Bus? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg0++;
		else{
			printf("[Creacion de Bus]\n\nInput Erroneo.\nPresione cualquier tecla para volver a intentar.\n");
			getch();
		}
	}
	free(qLic);
	free(buffer);
	free(qBuf);
	return res;
}

int busdltscr(sqlite3 *db){
    int res = 0;
	int flg = 0;
    int qId;
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*10);
	while(flg < 1){
		fflush(stdin);
		system("CLS");
		printf("[Eliminacion de Bus]\n\nIntroduzca un numero de bus valido\n\n");
		fgets(qBuf,10,stdin);
		sscanf(qBuf, "%d", &qId);
		if(qId < 1){
			fflush(stdin);
			printf("Numero Invalido o no existente;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
			getch();
		}
		else{
		fflush(stdin);
		flg++;
		eliminarBus(db, qId);
		}
	}
	flg--;
	while(flg == 0){
		system("CLS");
		printf("Quiere eliminar otro Bus? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg++;
		else{
			printf("[Eliminacion de Bus]\n\nInput erroneo\nPulse cualquier tecla para continuar\n");
			getch();
		}
	}
	free(buffer);
	free(qBuf);
	return res;
}

void visualizarBuses(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	int result;
	char* query = malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM bus");
	char* query2;
	//atrib. bus
	char* qLic;
	int qSeats;
	int qId;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Trip: perfecto
	system("CLS");
	printf("[LISTA DE BUSES]\n\n");
	for(int i = 0; i <= numR; i++){
		qLic = malloc(sizeof(char)*10);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM bus where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
            strcpy(qLic,sqlite3_column_text(stmt, 1));
			qSeats = sqlite3_column_int(stmt, 2);
			printf("[ID] %d [Matricula] %s [Asientos] %d \n", qId, qLic, qSeats);
		}
		free(qLic);
		free(query2);
	}
	sqlite3_finalize(stmt);
	printf("\n\n[PRESIONAR CUALQUIER TECLA PARA CONTINUAR]");
	getch();
	
}

void imprimirBuses(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	FILE* f;
	f = fopen("Bus.txt", "w");
	int result;
	char* query =  malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM bus");
	char* query2;
	//atrib. bus
	char* qLic;
	int qSeats;
	int qId;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Viaje: perfecto
	system("CLS");
	printf("[IMPRIMIENDO BUSES]\n\n");
	for(int i = numR; i > 0; i--){
		qLic = malloc(sizeof(char)*10);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM bus where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
            strcpy(qLic,sqlite3_column_text(stmt, 1));
			qSeats = sqlite3_column_int(stmt, 2);
			fprintf(f, "[ID] %d [Matricula] %s [Asientos] %d \n", qId, qLic, qSeats);
		}
		free(qLic);
		free(query2);
	}
	fclose(f);
	sqlite3_finalize(stmt);
	printf("\n\n[BUSES IMPRESOS, PULSE CUALQUIER TECLA PARA CONTINUAR]");
	getch();
}