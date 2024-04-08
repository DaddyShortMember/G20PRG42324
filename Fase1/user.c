#include "user.h"
//TODO: Make sure everything works, fix queries,

//Menus
int usmodscr(sqlite3 *db){
	//Opciones para modificar aspectos del usuario [name,email,contrasenya, y permisos de admin. local]
	int res = 0;
	int flg = 0;
	//Memoria dinamica:
	char* qEma = malloc(sizeof(char)*30);
	//Aqui declaramos el puntero, y de inmediato lo hacemos dinamico al reservar 1 byte * 30 (30 bytes) en RAM.
	//Es un array de 30 posiciones [0-29].
	char* qVar = malloc(sizeof(char)*30);
	char* qBuf = malloc(sizeof(char)*30);
	char* buffer = malloc(sizeof(char)*3);
	int qAut;
	int choice;
	while(flg < 1){
		fflush(stdin);
		system("CLS");
		printf("[Modificacion de Usuario]\n\nIntroduzca un correo electronico valido\n\n");
		fgets(qBuf,30,stdin);
		sscanf(qBuf, "%s", qEma);
		if(strlen(qEma) > 30 || exists(db, qEma) == 0){
			fflush(stdin);
			printf("Email Invalido o no existente;\nPor favor, introduzca un email valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
			getch();
		}
		else{
		fflush(stdin);
		flg++;
		}
	}
	free(qBuf);
	qBuf = malloc(sizeof(char)*30);
	flg--;
	while(flg == 0){
	fflush(stdin);
	system("CLS");
	printf("[MODIFICAR ATRIBUTO DE USUARIO]\n");
	printf("[1] Contrasenya\n"); 
	printf("[2] Nombre\n"); 
	printf("[3] Autorizacion\n");
	printf("[0] Volver\n");
	printf("Introduzca su seleccion:\n");
	fgets(buffer,3,stdin);
	sscanf(buffer, "%d", &choice);
	switch(choice){
		case 0: flg++;
				break;
		case 1: //Mod. Contrasenya
				while(flg < 1){
					fflush(stdin);
					system("CLS");
					printf("[Modificacion de Usuario]\n\nIntroduzca una contrasenya valida\n\n");
					fgets(qBuf,30,stdin);
					sscanf(qBuf, "%s", qVar);
					if(strlen(qVar) > 30){ 
						fflush(stdin);
						printf("Contrasenya Invalida;\nPor favor, introduzca una contrasenya valida\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
						getch();
					}else{
						fflush(stdin);
						flg++;
					}
				}
				modificarContrasenya(db, qEma, qVar);
				break;
		case 2: //Mod. name
				while(flg < 1){
					fflush(stdin);
					system("CLS");
					printf("[Modificacion de Usuario]\n\nIntroduzca un nombre valido\n\n");
					fgets(qBuf,30,stdin);
					sscanf(qBuf, "%s", qVar);
					if(strlen(qVar) > 30){ 
						fflush(stdin);
						printf("Nombre Invalido;\nPor favor, introduzca un nombre valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
						getch();
					}else{
						fflush(stdin);
						flg++;
					}
				}
				modificarName(db, qEma, qVar);
				break;
		case 3: //Mod. Aut
			while(flg < 1){
					fflush(stdin);
					system("CLS");
					printf("[Modificacion de Usuario]\n\nIntroduzca un nivel valido\n[1] ADMIN\n[2] EMPRESA\n[3] USUARIO NORMAL\n\n");
					fgets(qBuf,2,stdin);
					sscanf(qBuf, "%d", &qAut);
					if(qAut < 0 || qAut > 3){ 
						fflush(stdin);
						printf("Nivel Invalido;\nPor favor, introduzca un nivel valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
						getch();
					}else{
						fflush(stdin);
						flg++;
					}
				}
				modificarAut(db, qEma, qAut);
				break;
		default: 
				system("CLS");
				printf("Opcion Invalida;\nPor favor, introduzca un numero que aparezca en el menu\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
				getch();
				break;
		}
	}
	flg--;
	while(flg == 0){
		system("CLS");
		printf("Quiere modificar otro usuario? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg++;
		else{
			printf("[Modificacion de Usuario]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
			getch();
		}
	}
	free(qEma);
	free(qVar);
	free(qBuf);
	free(buffer);
	return res;
} 
int usrcrtscr(sqlite3 *db){
	//Menu de creacion de usuario
	char* qNom = malloc(sizeof(char)*30);
	char* qEma = malloc(sizeof(char)*30);
	char* qCon = malloc(sizeof(char)*30);
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*30);
	int qAut;
	int res = 0;
	Usuario qUsua;
	int flg = 0;
	int flg2 = 0;
	int flg3 = 0;
	int flg4 = 0;
	while(flg < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Usuario]\n\nIntroduzca un nombre de usuario valido\n\n");
	fgets(qBuf,30,stdin);
	sscanf(qBuf, "%s", qNom);
	if(strlen(qNom) > 30){ 
		fflush(stdin);
		printf("Usuario Invalido;\nPor favor, introduzca un usuario valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg++;
	}
	}
	while(flg2 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Usuario]\n\nIntroduzca un correo electronico valido\n\n");
	fgets(qBuf,30,stdin);
	sscanf(qBuf, "%s", qEma);
	if(strlen(qEma) > 30 || exists(db, qEma) == 1){
		fflush(stdin);
		printf("Email Invalido o repetido;\nPor favor, introduzca un email valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg2++;
	}
	}
	while(flg3 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Usuario]\n\nIntroduzca una contrasenya valida\n\n");
	fgets(qBuf,30,stdin);
	sscanf(qBuf, "%s", qCon);
	if(strlen(qCon) > 30){ 
		fflush(stdin);
		printf("Contrasenya Invalida;\nPor favor, introduzca una contrasenya valida\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}else{
		fflush(stdin);
		flg3++;
	}
	}
	while(flg4 < 1){
	fflush(stdin);
	system("CLS");
	printf("[Creacion de Usuario]\n\nIntroduzca un nivel de autoridad valido:\n[1] ADMIN\n[2] EMPRESA\n[3] USUARIO NORMAL\n\n");
	fgets(qBuf,2,stdin);
	sscanf(qBuf, "%d",&qAut);
	if(qAut < 0 || qAut > 3){ 
		fflush(stdin);
		printf("Nivel Invalido;\nPor favor, introduzca un nivel valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg4++;
		flg--;
	}
	}
	qUsua = creaUsuario(qNom,qEma,qCon,qAut);
	anyadirUsuario(db,qUsua);
	printf("[Creacion de Usuario]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
	getch();
	while(flg == 0){
		system("CLS");
		printf("Quiere anyadir otro usuario? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg++;
		else{
			printf("[Creacion de Usuario]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
			getch();
		}
	}
	free(qNom);
	free(qCon);
	free(qEma);
	free(buffer);
	free(qBuf);
	return res;
}
int usrdltscr(sqlite3 *db){
	int res = 0;
	int flg = 0;
	char* buffer = malloc(sizeof(char)*2);
	char* qEma = malloc(sizeof(char)*30);
	char* qBuf = malloc(sizeof(char)*30);
	while(flg < 1){
		fflush(stdin);
		system("CLS");
		printf("[Eliminacion de Usuario]\n\nIntroduzca un correo electronico valido\n\n");
		fgets(qBuf,30,stdin);
		sscanf(qBuf, "%s", qEma);
		if(strlen(qEma) > 30 || exists(db, qEma) == 0){
			fflush(stdin);
			printf("Email Invalido o no existente;\nPor favor, introduzca un email valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
			getch();
		}
		else{
		fflush(stdin);
		flg++;
		eliminarUsuario(db, qEma);
		}
	}
	flg--;
	while(flg == 0){
		system("CLS");
		printf("Quiere eliminar otro usuario? (1/0)\n");
		fgets(buffer,2,stdin);
		sscanf(buffer, "%d", &res);
		if(res == 1 || res == 0)
			flg++;
		else{
			printf("[Eliminacion de Usuario]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
			getch();
		}
	}
	free(buffer);
	free(qBuf);
	free(qEma);
	return res;
	}

//TODO: Make sure everything works, fix queries,

//Funciones
//Cambiar arrays directos a malloc.
Usuario getUser(sqlite3 *db, char* email){ //TODO: MALLOC!; fix query
	sqlite3_stmt *stmt;
	Usuario qUsua;
	int result;
	//Query: select (name, pass, id, auth, mail) from User where mail=%s
	char* query = malloc(sizeof(char)*1028);
	sprintf(query, "select * from user where mail = '%s'", email);
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	if (result == SQLITE_ROW) { //Si existe el email en la BD:
		qUsua.id = sqlite3_column_int(stmt, 0);
		strcpy(qUsua.name,sqlite3_column_text(stmt, 1));
		strcpy(qUsua.mail,sqlite3_column_text(stmt, 2));
		strcpy(qUsua.pass,sqlite3_column_text(stmt, 3));
		qUsua.auth = sqlite3_column_int(stmt, 4);
	}else{
		system("CLS");
		qUsua.id = 0;
		printf("Usuario no existe.");
		getch();
	}
	sqlite3_finalize(stmt);
	free(query);
	return qUsua;
}
Usuario creaUsuario(char name[30],char email[30],char pass[30],int auth){
	Usuario qUsua;
	strcpy(qUsua.name, name);
	strcpy(qUsua.mail, email);
	strcpy(qUsua.pass, pass);
	qUsua.auth = auth;
	return qUsua;
}
void anyadirUsuario(sqlite3 *db,  Usuario usuario){ //Funciona, pero da error por alguna razon
	char* query = malloc(sizeof(char)*256);
	sqlite3_stmt *stmt;
	int result;
	sprintf(query, "insert into User (id, name, mail, pass, auth) values (NULL,'%s','%s','%s',%d)", usuario.name, usuario.mail, usuario.pass, usuario.auth);
	result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error al preparar el query (INSERT)\n");
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error al introducir usuario\n");
	}else{
		printf("Usuario %s introducido\n", usuario.mail);
	}
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}
void modificarAut(sqlite3 *db, char* email, int aut){ 
	int id;
	int result;
	sqlite3_stmt *stmt;
	char* query = malloc(sizeof(char)*256);
	sprintf(query, "select id from User where mail = '%s'", email);
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	id = sqlite3_column_int(stmt, 0);
	if(id > 1){
		if(result == SQLITE_ROW){
			free(query);
			query = malloc(sizeof(char)*256);
			sprintf(query, "UPDATE user SET auth = %d WHERE id = %d", aut, id);
			sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
			result = sqlite3_step(stmt);
		}else{
			printf("Usuario no existe.");
		}
	}else{
		printf("Usuario no valido.");
	}
	free(query);
	sqlite3_finalize(stmt);
}
int exists(sqlite3 *db, char* email){ 
	int result;
	int ret;
	sqlite3_stmt *stmt;
	char* geid = malloc(sizeof(char)*128);
	Usuario qUs;
	sprintf(geid, "select id from User where mail = '%s' ", email);
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	result = sqlite3_step(stmt);
	if(result == SQLITE_ROW){
		qUs = getUser(db, email);
		if(qUs.auth == 1)
			ret = 1;
		else if(qUs.auth == 2)
			ret = 2;
		else
			ret = 3;
	}else{
		ret = 0;
	}
	logAppendDB(db, geid, result);
	sqlite3_finalize(stmt);
	free(geid);
	return ret;
}
int passCheck(sqlite3 *db, char* email, char* contrasenya){ 
	int result;
	int ret;
	char* qCon = malloc(sizeof(char)*30);
	sqlite3_stmt *stmt;
	char* geid = malloc(sizeof(char)*128);
	sprintf(geid, "select pass from User where mail = '%s'", email);
	printf("\nDEBUG: %s", geid);
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	result = sqlite3_step(stmt);
	if(result == SQLITE_ROW){
		  strcpy(qCon,sqlite3_column_text(stmt, 0));
		  printf("\nDEBUG: %s", qCon);
		if(strcmp(qCon,contrasenya) == 0)
			ret = 1;
		else
			ret = 0;
	}else{
		ret = 0;
	}
	logAppendDB(db, geid, result);
	free(qCon);
	sqlite3_finalize(stmt);
	return ret;
}
void modificarContrasenya(sqlite3 *db, char* email, char* contrasenya){ //MALLOC!
	char* query = malloc(sizeof(char)*256);
	sprintf(query, "UPDATE user SET pass = '%s' WHERE mail = '%s'",contrasenya,email);
	sqlite3_stmt *stmt;
	int result;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}
void modificarName(sqlite3 *db, char* email, char* name){ //BIEN
	char* query = malloc(sizeof(char)*256);
	sprintf(query, "UPDATE user SET name = '%s' WHERE mail = '%s'",name,email);
	sqlite3_stmt *stmt;
	int result;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}
void eliminarUsuario(sqlite3 *db, char* email){ //BIEN
	Usuario qUser = getUser(db, email);
	if(qUser.id > 1){
	char* query =  malloc(sizeof(char)*256);
	sprintf(query, "delete from User where mail= '%s'",email);
	int result;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	sqlite3_finalize(stmt);
	}else{
		printf("Usuario invalido.\nPresione para continuar.");
		getch();
	}
}

//Funciones Visuales
void visualizarUsuarios(sqlite3 *db){ //MALLOC!
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	int result;
	char* query = malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM User");
	char* query2;
	//atrib. usuario
	char* qNom;
	char* qEma;
	char* qCon;
	int qAut;
	int qId;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de usuarios: perfecto
	system("CLS");
	printf("[LISTA DE USUARIOS]\n\n");
	for(int i = 0; i <= numR; i++){
		qEma = malloc(sizeof(char)*30);
		qNom = malloc(sizeof(char)*30);
		qCon = malloc(sizeof(char)*30);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM User where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
			strcpy(qNom,sqlite3_column_text(stmt, 1));
			strcpy(qEma,sqlite3_column_text(stmt, 2));
			strcpy(qCon,sqlite3_column_text(stmt, 3));
			qAut = sqlite3_column_int(stmt, 4);
			printf("[ID] %d [Nombre] %s [E-Mail] %s [Contrasenya] %s [Autoridad] %d \n", qId, qNom, qEma, qCon, qAut);
		}
		free(qEma);
		free(qNom);
		free(qCon);
		free(query2);
	}
	sqlite3_finalize(stmt);
	printf("\n\n[PRESIONAR CUALQUIER TECLA PARA CONTINUAR]");
	getch();
	
}
void imprimirUsuarios(sqlite3 *db){
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	FILE* f;
	f = fopen("usuarios.txt", "w");
	int result;
	char* query =  malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM User");
	char* query2;
	//atrib. usuario
	char* qNom;
	char* qEma;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	numR = sqlite3_column_int(stmt, 0); //Numero de usuarios: perfecto
	system("CLS");
	printf("[IMPRIMIENDO USUARIOS]\n\n");
	for(int i = numR; i > 0; i--){
		qEma = malloc(sizeof(char)*30);
		qNom = malloc(sizeof(char)*30);
		query2 = malloc(sizeof(char)*128);
		sprintf(query2, "SELECT * FROM User where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			strcpy(qNom,sqlite3_column_text(stmt, 1));
			strcpy(qEma,sqlite3_column_text(stmt, 2));
			fprintf(f, "[Nombre] %s [E-Mail] %s \n", qNom, qEma);
		}
		free(qEma);
		free(qNom);
		free(query2);
	}
	fclose(f);
	sqlite3_finalize(stmt);
	printf("\n\n[USUARIOS IMPRESOS, PULSE CUALQUIER TECLA PARA CONTINUAR]");
	getch();
}