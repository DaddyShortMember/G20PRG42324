#include "logger.h"

void logOpen(sqlite3 *db){
	FILE* f;
		char* date = malloc(sizeof(char)*128);
		char* query = malloc(sizeof(char)*128);
		sprintf(query, "SELECT datetime('now')");
		sqlite3_stmt *stmt;
		sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
		sqlite3_step(stmt);
		strcpy(date,sqlite3_column_text(stmt, 0));
		sqlite3_finalize(stmt);
		f = fopen("log.log", "a");
		fprintf(f, "[%s] BEGINNING\n", date);
		fclose(f);
		free(date);
		free(query);
}

void logStart(sqlite3 *db, char* user){
		FILE* f;
		char* date = malloc(sizeof(char)*128);
		char* query = malloc(sizeof(char)*128);
		sprintf(query, "SELECT datetime('now')");
		sqlite3_stmt *stmt;
		sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
		sqlite3_step(stmt);
		strcpy(date,sqlite3_column_text(stmt, 0));
		sqlite3_finalize(stmt);
		f = fopen("log.log", "a");
		fprintf(f, "[%s] %s logged in\n", date, user);
		fclose(f);
		free(date);
		free(query);
}

void logAppendDB(sqlite3 *db, char* statement, int result){ //Pone en fichero exactamente cada movimiento hecho a B.D.
		FILE* f;
		char* date = malloc(sizeof(char)*128);
		char* query = malloc(sizeof(char)*128);
		sprintf(query, "SELECT datetime('now')");
		sqlite3_stmt *stmt;
		sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
		sqlite3_step(stmt);
		strcpy(date,sqlite3_column_text(stmt, 0));
		sqlite3_finalize(stmt);
		f = fopen("log.log", "a");
		fprintf(f, "[%s] executed %s: ", date, statement);
		if(result==SQLITE_DONE)
			fprintf(f, "[OK]\n");
		else
			fprintf(f, "[ERROR]\n");
		fclose(f);
		free(date);
		free(query);
}

void logEnd(sqlite3 *db, char* user){
		FILE* f;
		char* date = malloc(sizeof(char)*128);
		char* query = malloc(sizeof(char)*128);
		sprintf(query, "SELECT datetime('now')");
		sqlite3_stmt *stmt;
		sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
		sqlite3_step(stmt);
		strcpy(date,sqlite3_column_text(stmt, 0));
		sqlite3_finalize(stmt);
		f = fopen("log.log", "a");
		fprintf(f, "[%s] %s logged out\n", date, user);
		fclose(f);
		free(date);
		free(query);
}

void logExit(sqlite3 *db){
		FILE* f;
		char* date = malloc(sizeof(char)*128);
		char* query = malloc(sizeof(char)*128);
		sprintf(query, "SELECT datetime('now')");
		sqlite3_stmt *stmt;
		sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
		sqlite3_step(stmt);
		strcpy(date,sqlite3_column_text(stmt, 0));
		sqlite3_finalize(stmt);
		f = fopen("log.log", "a");
		fprintf(f, "[%s] SHUTDOWN\n\n ", date);
		fclose(f);
		free(date);
		free(query);
}