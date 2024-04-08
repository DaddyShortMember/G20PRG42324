#include "stop.h"

Stop getStop(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	Stop qStop;
	int result;
	char* query = malloc(sizeof(char)*1028);
	sprintf(query, "select * from Stop where id = %d", id);
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	if (result == SQLITE_ROW) {
		qStop.id = sqlite3_column_int(stmt, 0);
		strcpy(qStop.license,sqlite3_column_text(stmt, 2));
	}else{
		system("CLS");
		qStop.id = 0;
		printf("Parada no existente.");
		getch();
	}
	sqlite3_finalize(stmt);
	free(query);
	return qStop;
}

Bus creaStop(char* name){
	Stop qStop;
    strcpy(qStop.name, name);
	return qStop;
}

void anyadirStop(sqlite3 *db, Stop stop){
    char* query = malloc(sizeof(char)*256);
	sqlite3_stmt *stmt;
	int result;
	sprintf(query, "insert into Stop (id, name) values (NULL, '%s')", stop.name);
	result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al preparar el query (INSERT)\n");
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error al introducir Stop\n");
	}else{
		printf("Stop introducido\n");
	}
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}


//Menus
void visualizarStops(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	int result;
	char* query = malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM stop");
	char* query2;
	//atrib. bus
	char* qName;
	int qId;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Trip: perfecto
	system("CLS");
	printf("[LISTA DE PARADAS]\n\n");
	for(int i = 0; i <= numR; i++){
		qName = malloc(sizeof(char)*30);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM stop where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
            strcpy(qName,sqlite3_column_text(stmt, 1));
			printf("[ID] %d [Licencia] %s [Asientos] %d \n", qId, qName);
		}
		free(qName);
		free(query2);
	}
	sqlite3_finalize(stmt);
	printf("\n\n[PRESIONAR CUALQUIER TECLA PARA CONTINUAR]");
	getch();

}

void imprimirStops(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	FILE* f;
	f = fopen("Stop.txt", "w");
	int result;
	char* query =  malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM stop");
	char* query2;
	//atrib. bus
	char* qName;
	int qId;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Viaje: perfecto
	system("CLS");
	printf("[IMPRIMIENDO PARADAS]\n\n");
	for(int i = numR; i > 0; i--){
		qName = malloc(sizeof(char)*30);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM stop where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
            strcpy(qName,sqlite3_column_text(stmt, 1));
			fprintf(f, "[ID] %d [Nombre] %s \n", qId, qName);
		}
		free(qName);
		free(query2);
	}
	fclose(f);
	sqlite3_finalize(stmt);
	printf("\n\n[PARADAS IMPRESAS, PULSE CUALQUIER TECLA PARA CONTINUAR]");
	getch();
}

int stopcrtrscr(sqlite3 *db){
    //Menu de creacion de Bus
	char* qName = malloc(sizeof(char)*10);
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*11);
	int res = 0;
	Stop qStop;
	int flg0 = 0;
	int flg1 = 0;
	while(flg0 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Parada]\n\nIntroduzca un nombre valido\n\n");
	fgets(qBuf,11,stdin);
	sscanf(qBuf, "%s", qName);
	if(strlen(qName) > 30){
		fflush(stdin);
		printf("Nombre Invalido;\nDebe tener un maximo de 10 digitos \n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}else{
		fflush(stdin);
		flg0++;
	}
	}
    flg0--;

	qStop = creaStop(qName);
	anyadirBus(db,qBus);
	printf("[Creacion de Parada]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
	getch();
	while(flg0 == 0){
		system("CLS");
		printf("Quiere anyadir otra Parada? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg0++;
		else{
			printf("[Creacion de Parada]\n\nInput Erronea.\nPresione cualquier tecla para volver a intentar.\n");
			getch();
		}
	}
	free(qName);
	free(buffer);
	free(qBuf);
	return res;
}
