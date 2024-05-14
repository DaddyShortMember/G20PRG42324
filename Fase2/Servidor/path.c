#include "path.h"

Path getPath(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	Path qPath;
	int result;
	char* query = malloc(sizeof(char)*1028);
	sprintf(query, "select * from Path where id = %d", id);
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	if (result == SQLITE_ROW) {
		qPath.id = sqlite3_column_int(stmt, 0);
		qPath.initialstop,sqlite3_column_text(stmt, 3);
		qPath.finalstop = sqlite3_column_int(stmt, 2);
	}else{
		system("CLS");
		qPath.id = 0;
		printf("Trayecto no existe.");
		getch();
	}
	sqlite3_finalize(stmt);
	free(query);
	return qPath;
}

Path creaPath(int initialStop, int finalStop){
    Path qPath;
    qPath.initialstop = initialStop;
	qPath.finalstop = finalStop;
	return qPath;
}

void anyadirPath(sqlite3 *db, Path path){
    char* query = malloc(sizeof(char)*256);
	sqlite3_stmt *stmt;
	int result;
	sprintf(query, "insert into Path (id, istop, fstop) values (NULL, %d, %d)", path.initialstop, path.finalstop);
	result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al preparar el query (INSERT)\n");
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error al introducir Trayecto\n");
	}else{
		printf("Trayecto introducido\n");
	}
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}


//Menus
int pathcrtrscr(sqlite3 *db){
    //Menu de creacion de Path
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*11);
	int qInitialStop;
	int qFinalStop;
	int res = 0;
	Path qPath;
	int flg0 = 0;
	int flg1 = 0;
	while(flg0 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Trayecto]\n\nIntroduzca el id de la primera parada\n\n");
	fgets(qBuf,11,stdin);
	sscanf(qBuf, "%d", &qInitialStop);
    if(qInitialStop < 0){
		fflush(stdin);
		printf("Parada Invalida;\nPor favor, introduzca un id de parada valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg0++;
	}
	}
    flg0--;
	while(flg1 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Path]\n\nIntroduzca el id de la segunda parada\n\n");
	fgets(qBuf,10,stdin);
	sscanf(qBuf, "%d", &qFinalStop);
	if(qFinalStop < 0){
		fflush(stdin);
		printf("Parada Invalida;\nPor favor, introduzca un id de parada valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg1++;
	}
	}
    flg1--;
	qPath = creaPath(qInitialStop,qFinalStop);
	anyadirPath(db,qPath);
	printf("[Creacion de Trayecto]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
	getch();
	while(flg0 == 0){
		system("CLS");
		printf("Quiere anyadir otro Trayecto? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg0++;
		else{
			printf("[Creacion deTrayecto]\n\nInput Erroneo.\nPresione cualquier tecla para volver a intentar.\n");
			getch();
		}
	}
	free(buffer);
	free(qBuf);
	return res;
}


void visualizarCaminos(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	int result;
	char* query = malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM Path");
	char* query2;
	int qInitialStop;
	int qFinalStop;
	int qId;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Trip: perfecto
	system("CLS");
	printf("[LISTA DE TRAYECTOS]\n\n");
	for(int i = 0; i <= numR; i++){
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM Path where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
			qInitialStop = sqlite3_column_int(stmt, 1);
			qFinalStop = sqlite3_column_int(stmt, 2);
			printf("[ID] %d [ParadaInicial] %d [ParadaFinal] %d \n", qId, qInitialStop, qFinalStop);
		}
		free(query2);
	}
	sqlite3_finalize(stmt);
	printf("\n\n[PRESIONAR CUALQUIER TECLA PARA CONTINUAR]");
	getch();

}

void imprimirCaminos(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	FILE* f;
	f = fopen("Path.txt", "w");
	int result;
	char* query =  malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM Path");
	char* query2;
	//atrib. Path
	int qInitialStop;
	int qFinalStop;
	int qId;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Viaje: perfecto
	system("CLS");
	printf("[IMPRIMIENDO TRAYECTOS]\n\n");
	for(int i = numR; i > 0; i--){
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM path where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
			qInitialStop = sqlite3_column_int(stmt, 1);
			qFinalStop = sqlite3_column_int(stmt, 2);
			fprintf(f, "[ID] %d [ParadaInicial] %s [ParadaFinal] %d \n", qId, qInitialStop, qFinalStop);
		}
		free(query2);
	}
	fclose(f);
	sqlite3_finalize(stmt);
	printf("\n\n[TRAYECTOS IMPRESOS, PULSE CUALQUIER TECLA PARA CONTINUAR]");
	getch();
}