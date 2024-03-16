#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#ifndef USUARIO_H_
#define USUARIO_H_

//Cambiar las funciones para incluir un fichero log

typedef struct{
	int id;
	char nombre[30];
	char mail[30];
	char pass[30];
	int auth; // 1 - Administrador 2 - Usuario especial 3 - Usuario normal
}Usuario; //X Bytes, malloc necesario para arrays

//Menus extras
int usmodscr(sqlite3 *db); //Opciones para modificar aspectos del usuario [nombre,email,pass,auth, y permisos de admin. local]
int usrcrtscr(sqlite3 *db); //Menu de creacion de usuario
int usrdltscr(sqlite3 *db); //Para eliminar un usuario

//Funciones
Usuario getUser(sqlite3 *db, char* email);
Usuario creaUsuario(char nombre[30],char email[30],char pass[30],int auth);
void anyadirUsuario(sqlite3 *db, Usuario usuario);
void grantAdmin(sqlite3 *db, char* email);
void removeAdmin(sqlite3 *db, char* email);
int isAdmin(sqlite3 *db, char* email);
int exists(sqlite3 *db, char* email);
int exists2(sqlite3 *db, int id);
int passCheck(sqlite3 *db, char* email, char* pass);
void modificarNombre(sqlite3 *db, char* email, char* nombre);
void modificarAuth(sqlite3 *db, char* email, int auth);
void modificarpass(sqlite3 *db, char* email, char* pass);
void eliminarUsuario(sqlite3 *db, char* email);

//Funciones Visuales
//Perfectas para malloc??:
void visualizarUsuarios(sqlite3 *db); //Muestra en pantalla todos los usuarios, array de Usuarios??
void imprimirUsuarios(sqlite3 *db); //Exporta todos los usuarios existentes en un .txt, array de Usuarios?

#endif /* USUARIO_H_ */
