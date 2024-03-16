#include "user.h"

//Menus
int usmodscr(sqlite3 *db){
	//Opciones para modificar aspectos del usuario [nombre,email,contrasenya,saldo, y permisos de admin. local]
	int res = 0;
	int flg = 0;
	//Memoria dinamica:
	char* qEma = malloc(sizeof(char)*30);
	//Aqui declaramos el puntero, y de inmediato lo hacemos dinamico al reservar 1 byte * 30 (30 bytes) en RAM.
	//Es un array de 30 posiciones [0-29].
	char* qVar = malloc(sizeof(char)*30);
	char* qBuf = malloc(sizeof(char)*30);
	char* buffer = malloc(sizeof(char)*3);
	char* authB = malloc(sizeof(int));
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
	printf("[4] Permiso de Administrador\n");
	if(isAdmin(db, qEma) == 0)
		printf("(%s no tiene permisos de administrador.)\n", qEma);
	else
		printf("(%s tiene permisos de administrador.)\n", qEma);
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
		case 2: //Mod. Nombre
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
				modificarNombre(db, qEma, qVar);
				break;
		case 3: //Mod. Aut
				while(flg < 1){
					fflush(stdin);
					system("CLS");
					printf("[Modificacion de Usuario]\n\nIntroduzca un saldo valido\n\n");
					fgets(authB,11,stdin);
					sscanf(authB, "%d",&qAut);
					if(qAut < 0){ 
						fflush(stdin);
						printf("Saldo Invalido;\nPor favor, introduzca un saldo valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
						getch();
					}
					else{
						fflush(stdin);
						flg++;
					}
				}
				modificarSaldo(db, qEma,qAut);
				break;
		case 4: //Dar Admin
				grantAdmin(db, qEma);
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
	free(authB);
	return res;
} 
int usrcrtscr(sqlite3 *db){
	//Menu de creacion de usuario
	char* qNom = malloc(sizeof(char)*30);
	char* qEma = malloc(sizeof(char)*30);
	char* qCon = malloc(sizeof(char)*30);
	char* buffer = malloc(sizeof(char)*2);
	char* qBuf = malloc(sizeof(char)*30);
	char* salB = malloc(sizeof(char)*10);
	int qSal;
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
	printf("[Creacion de Usuario]\n\nIntroduzca un saldo valido\n\n");
	fgets(salB,10,stdin);
	sscanf(salB, "%d",&qSal);
	if(qSal < 0){ 
		fflush(stdin);
		printf("Saldo Invalido;\nPor favor, introduzca un saldo valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
		getch();
	}
	else{
		fflush(stdin);
		flg4++;
		flg--;
	}
	}
	qUsua = creaUsuario(qNom,qEma,qCon,qSal);
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
	free(salB);
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

//TODO: Fix i

//Funciones
//Cambiar arrays directos a malloc.
Usuario getUser(sqlite3 *db, char* email){ //MALLOC!
	sqlite3_stmt *stmt;
	Usuario qUsua;
	int result;
	char* geno = "select nombre from Usuario where mail=?";
	char* geco = "select pass from Usuario where mail=?";
	char* geid = "select id from Usuario where mail=?";
	char* gesa = "select auth from Usuario where mail=?";
	char* gema = "select mail from Usuario where mail=?";
	sqlite3_prepare_v2(db, gema, strlen(gema), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) { //Si existe el email en la BD:
	strcpy(qUsua.mail, (char*) sqlite3_column_text(stmt, 0));
	sqlite3_prepare_v2(db, geno, strlen(geno), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
			strcpy(qUsua.nombre, (char*) sqlite3_column_text(stmt, 0));
		}
	sqlite3_prepare_v2(db, geco, strlen(geco), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
			strcpy(qUsua.pass, (char*) sqlite3_column_text(stmt, 0));
		}
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
			qUsua.id = sqlite3_column_int(stmt, 0);
		}
	sqlite3_prepare_v2(db, gesa, strlen(gesa), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
			qUsua.auth = sqlite3_column_int(stmt, 0);
		}
		}else{
			system("CLS");
			qUsua.id = 0;
			printf("Usuario no existe.");
			getch();
		}
	sqlite3_finalize(stmt);
	return qUsua;
}
Usuario creaUsuario(char nombre[30],char email[30],char pass[30],int auth){
	Usuario qUsua;
	strcpy(qUsua.nombre, nombre);
	strcpy(qUsua.mail, email);
	strcpy(qUsua.pass, pass);
	qUsua.auth = auth;
	return qUsua;
}
void anyadirUsuario(sqlite3 *db,  Usuario usuario){ //BIEN
	char* query = malloc(sizeof(char)*256);
	sqlite3_stmt *stmt;
	int result;
	sprintf(query, "insert into usuario (id, nombre, mail, pass, auth) values (NULL,'%s','%s','%s',%d)", usuario.nombre, usuario.mail, usuario.pass, usuario.auth);
	result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
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
void grantAdmin(sqlite3 *db, char* email){ //TODO: Change to fetch value from table; MALLOC!
	int id;
	int result;
	sqlite3_stmt *stmt;
	char* geid = "select id from Usuario where mail=?";
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	id = sqlite3_column_int(stmt, 0);
	if(result == SQLITE_ROW){
		FILE* f;
		f = fopen("ad.min", "a");
		fprintf(f, "%d\n",id);
		fclose(f);
	}else{
		printf("Usuario no existe.");
	}
	sqlite3_finalize(stmt);
}
int isAdmin(sqlite3 *db, char* email){ //TODO: Change to fetch value from table; MALLOC!
	int id;
	int result;
	int ret = 0;
	int qId;
	sqlite3_stmt *stmt;
	char* geid = "select perm from Usuario where mail=?";
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	id = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return ret;
}
int exists(sqlite3 *db, char* email){ //MALLOC!
	int result;
	int ret;
	sqlite3_stmt *stmt;
	char* geid = "select id from Usuario where mail=?";
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if(result == SQLITE_ROW){
		ret = 1;
	}else{
		ret = 0;
	}
	logAppendDB(db, geid, result);
	sqlite3_finalize(stmt);
	return ret;
}
int exists2(sqlite3 *db, int id){ //MALLOC!
	int result;
	int ret;
	sqlite3_stmt *stmt;
	char* geid = "select id from Usuario where id=?";
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	result = sqlite3_step(stmt);
	if(result == SQLITE_ROW){
		ret = 1;
	}else{
		ret = 0;
	}
	logAppendDB(db, geid, result);
	sqlite3_finalize(stmt);
	return ret;
}
int passCheck(sqlite3 *db, char* email, char* contrasenya){ //MALLOC!
	int result;
	int ret;
	char* qCon = malloc(sizeof(char)*30);
	sqlite3_stmt *stmt;
	char* geid = "select contrasenya from Usuario where mail=?";
	sqlite3_prepare_v2(db, geid, strlen(geid), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if(result == SQLITE_ROW){
		  strcpy(qCon,sqlite3_column_text(stmt, 0));
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
void modificarSaldo(sqlite3 *db, char* email, int saldo){ //MALLOC!
	char* query = malloc(sizeof(char)*256); //"UPDATE usuario SET saldo = ? WHERE mail = ?";
	sqlite3_stmt *stmt;
	int result;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	sqlite3_bind_int(stmt, 1, saldo);
	sqlite3_bind_text(stmt, 2, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}
void modificarContrasenya(sqlite3 *db, char* email, char* contrasenya){ //MALLOC!
	char* query = malloc(sizeof(char)*256);
	//"UPDATE usuario SET contrasenya = ? WHERE mail = ?";
	sqlite3_stmt *stmt;
	int result;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, contrasenya, strlen(contrasenya), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}
void modificarNombre(sqlite3 *db, char* email, char* nombre){ //BIEN
	char* query = malloc(sizeof(char)*256);
	sprintf(query, "UPDATE usuario SET nombre = %s WHERE mail = %s",nombre,email);
	sqlite3_stmt *stmt;
	int result;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	logAppendDB(db, query, result);
	free(query);
	sqlite3_finalize(stmt);
}
void eliminarUsuario(sqlite3 *db, char* email){ //BIEN
	char* query =  malloc(sizeof(char)*256);
	sprintf(query, "delete from usuario where mail= %s",email);
	int result;
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
	result = sqlite3_step(stmt);
	free(query);
	sqlite3_finalize(stmt);
}

//Funciones Visuales
void visualizarUsuarios(sqlite3 *db){ //MALLOC!
	int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
	int result;
	char* query = malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM usuario");
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
		sprintf(query2, "SELECT * FROM usuario where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			qId = sqlite3_column_int(stmt, 0);
			strcpy(qNom,sqlite3_column_text(stmt, 1));
			strcpy(qEma,sqlite3_column_text(stmt, 2));
			strcpy(qCon,sqlite3_column_text(stmt, 3));
			qAut = sqlite3_column_int(stmt, 4);
			printf("[ID] %d [Nombre] %s [E-Mail] %s [Contrasenya] %s [Saldo] %d \n", qId, qNom, qEma, qCon, qAut);
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
	f = fopen("usuarios.tbl", "w");
	int result;
	char* query =  malloc(sizeof(char)*128);
	sprintf(query, "SELECT MAX(id) FROM usuario");
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
		sprintf(query2, "SELECT * FROM usuario where id = %d", i);
		sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW){
			logAppendDB(db, query2, SQLITE_DONE);
			strcpy(qNom,sqlite3_column_text(stmt, 1));
			strcpy(qEma,sqlite3_column_text(stmt, 2));
			fprintf(f, "[Nombre] %s [E-Mail] %s [Saldo] %d \n", qNom, qEma);
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