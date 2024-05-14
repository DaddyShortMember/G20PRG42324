#include "trip.h"
//TODO: Make sure everything works, fix queries,

Trip getTrip(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	Trip qTrip;
	int result;
	char* query = malloc(sizeof(char)*1028);
	sprintf(query, "select * from trip where id = %d", id);
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	if (result == SQLITE_ROW) {
		qTrip.id = sqlite3_column_int(stmt, 0);
		qTrip.busid = sqlite3_column_int(stmt, 1);
		qTrip.pathid = sqlite3_column_int(stmt, 2);
        strcpy(qTrip.etime,sqlite3_column_text(stmt, 3));
        strcpy(qTrip.atime,sqlite3_column_text(stmt, 4));
        qTrip.price = sqlite3_column_int(stmt, 5);
	}else{
		system("CLS");
		qTrip.id = 0;
		printf("Viaje no existe.");
		getch();
	}
	sqlite3_finalize(stmt);
	free(query);
	return qTrip;
}

Trip creaTrip( int busid, int pathid, char* etime, char* atime, int price){
    Trip qTrip;
	qTrip.busid = busid;
	qTrip.pathid = pathid;
	strcpy(qTrip.etime, etime);
	strcpy(qTrip.atime, atime);
	qTrip.price = price;
	return qTrip;
}

void anyadirTrip(sqlite3 *db, Trip trip){
    char* query = malloc(sizeof(char)*256);
	sqlite3_stmt *stmt;
	int result;
	sprintf(query, "insert into Trip (id, bus, path, etime, atime, price) values (NULL, %d, %d,'%s','%s',%d)", trip.busid, trip.pathid, trip.etime, trip.atime, trip.price);
	result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al preparar el query (INSERT)\n");
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error al introducir viaje (Posiblemente por no seguir el formato de hora indicado.)\n");
	}else{
		printf("Viaje introducido\n");
	}
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}

void eliminarTrip(sqlite3 *db, int id){
	char* query =  malloc(sizeof(char)*256);
	sprintf(query, "delete from Trip where id= %d",id);
	int result;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	sqlite3_finalize(stmt);
}

//Menus
int trpcrtrscr(sqlite3 *db){
    //Menu de creacion de viaje
	char* qHs = malloc(sizeof(char)*8);
	char* qHl = malloc(sizeof(char)*8);
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*10);
	int qPrice;
	int qBusid;
	int qPathid;
	int res = 0;
	Trip qTrip;
	int flg0 = 0;
	int flg1 = 0;
	while(flg0 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Viaje]\n\nIntroduzca un numero de bus valido\n\n");
	fgets(qBuf,10,stdin);
	sscanf(qBuf, "%d", &qBusid);
	if(qBusid < 0){ 
		fflush(stdin);
		printf("Numero de bus invalido;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
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
	printf("[Creacion de Viaje]\n\nIntroduzca un numero de ruta valido\n\n");
	fgets(qBuf,10,stdin);
	sscanf(qBuf, "%d", &qPathid);
	if(qPathid < 0){ 
		fflush(stdin);
		printf("Numero Invalido;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg1++;
	}
	}
    flg1--;
	while(flg0 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Viaje]\n\nIntroduzca una hora de salida valida\n\n");
	fgets(qBuf,9,stdin);
	sscanf(qBuf, "%s",qHs);
	if(strlen(qHs) != 8){ 
		fflush(stdin);
		printf("Hora Invalida;\nPor favor, introduzca una hora [HH:MM:SS] valida\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
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
	printf("[Creacion de Viaje]\n\nIntroduzca una hora de llegada valida\n\n");
	fgets(qBuf,9,stdin);
	sscanf(qBuf, "%s", qHl);
	if(strlen(qHl) != 8){ 
		fflush(stdin);
		printf("Hora Invalida;\nPor favor, introduzca una hora [HH:MM:SS] valida\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg1++;
	}
	}
    flg1--;
    while(flg0 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Viaje]\n\nIntroduzca un precio valido\n\n");
	fgets(qBuf,10,stdin);
	sscanf(qBuf, "%d", &qPrice);
	if(qBusid < 0){ 
		fflush(stdin);
		printf("Precio invalido;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg0++;
	}
	}
    flg0--;
	qTrip = creaTrip(qBusid,qPathid,qHs,qHl,qPrice);
	anyadirTrip(db,qTrip);
	printf("[Creacion de Viaje]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
	getch();
	while(flg0 == 0){
		system("CLS");
		printf("Quiere anyadir otro Viaje? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg0++;
		else{
			printf("[Creacion de Viaje]\n\nInput Erroneo.\nPresione cualquier tecla para volver a intentar.\n");
			getch();
		}
	}
	free(qHs);
	free(qHl);
	free(buffer);
	free(qBuf);
	return res;
}

int trpdltscr(sqlite3 *db){
    int res = 0;
	int flg = 0;
    int qId;
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*10);
	while(flg < 1){
		fflush(stdin);
		system("CLS");
		printf("[Eliminacion de Viaje]\n\nIntroduzca un numero de viaje valido\n\n");
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
		eliminarTrip(db, qId);
		}
	}
	flg--;
	while(flg == 0){
		system("CLS");
		printf("Quiere eliminar otro Viaje? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg++;
		else{
			printf("[Eliminacion de Viaje]\n\nInput erroneo\nPulse cualquier tecla para continuar\n");
			getch();
		}
	}
	free(buffer);
	free(qBuf);
	return res;
}

//Funciones Visuales
void visualizarTrip(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	//Aveces hace crash despues de crear un viaje. Es raro.
	int result;
	char* query = malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM trip");
	char* query2;
	//atrib. viaje
	char* qHs;
	char* qHl;
	int qBus;
    int qPath;
	int qId;
	int qPrice;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Trip: perfecto
	system("CLS");
	printf("[LISTA DE VIAJES]\n\n");
	for(int i = 0; i <= numR; i++){
		qHs = malloc(sizeof(char)*8);
		qHl = malloc(sizeof(char)*8);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM trip where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
			qBus = sqlite3_column_int(stmt, 1);
			qPath = sqlite3_column_int(stmt, 2);
			strcpy(qHs,sqlite3_column_text(stmt, 3));
			strcpy(qHl,sqlite3_column_text(stmt, 4));
			qPrice = sqlite3_column_int(stmt, 5);
			printf("[ID] %d [busID] %d [pathID] %d [Hora Salida] %s [Hora Llegada] %s [Precio] %d \n", qId, qBus, qPath, qHs, qHl, qPrice);
		}
		free(qHs);
		free(qHl);
		free(query2);
	}
	sqlite3_finalize(stmt);
	printf("\n\n[PRESIONAR CUALQUIER TECLA PARA CONTINUAR]");
	getch();
	
}
void imprimirTrip(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	FILE* f;
	f = fopen("Trip.txt", "w");
	int result;
	char* query =  malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM trip");
	char* query2;
	//atrib. usuario
	char* qHs;
	char* qHl;
	int qBus;
    int qPath;
	int qId;
	int qPrice;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de Trip: perfecto
	system("CLS");
	printf("[IMPRIMIENDO VIAJES]\n\n");
	for(int i = numR; i > 0; i--){
		qHs = malloc(sizeof(char)*8);
		qHl = malloc(sizeof(char)*8);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM trip where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
			qBus = sqlite3_column_int(stmt, 1);
			qPath = sqlite3_column_int(stmt, 2);
			strcpy(qHs,sqlite3_column_text(stmt, 3));
			strcpy(qHl,sqlite3_column_text(stmt, 4));
			qPrice = sqlite3_column_int(stmt, 5);
			fprintf(f, "[ID] %d [busID] %d [pathID] %d [Hora Salida] %s [Hora Llegada] %s [Precio] %d \n", qId, qBus, qPath, qHs, qHl, qPrice);
		}
		free(qHs);
		free(qHl);
		free(query2);
	}
	fclose(f);
	sqlite3_finalize(stmt);
	printf("\n\n[VIAJES IMPRESOS, PULSE CUALQUIER TECLA PARA CONTINUAR]");
	getch();
}