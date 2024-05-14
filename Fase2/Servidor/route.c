#include "route.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

Route getRoute(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
    Route qRoute;
    int result;
    char* query = malloc(sizeof(char)*1028);
    sprintf(query, "SELECT * FROM route WHERE id = %d", id);
    sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
    result = sqlite3_step(stmt);
    free(query);
    if (result == SQLITE_ROW) {
        qRoute.id = sqlite3_column_int(stmt, 0);
        qRoute.pathid = sqlite3_column_int(stmt, 1);
        qRoute.currentstopid = sqlite3_column_int(stmt, 2);
        qRoute.nextstopid = sqlite3_column_int(stmt, 3);
        qRoute.ordernumber = sqlite3_column_int(stmt, 4);
    } else {
        printf("Ruta no encontrada.\n");
        qRoute.id = 0;
        qRoute.pathid = 0;
        qRoute.currentstopid = 0;
        qRoute.nextstopid = 0;
        qRoute.ordernumber = 0;
    }
    sqlite3_finalize(stmt);
    return qRoute;
}

Route creaRoute(int pathid, int currentstopid, int nextstopid, int ordernumber) {
    Route route;
    route.pathid = pathid;
    route.currentstopid = currentstopid;
    route.nextstopid = nextstopid;
    route.ordernumber = ordernumber;
    return route;
}

void anyadirRoute(sqlite3 *db, Route Route){
    char* query = malloc(sizeof(char)*256);
    sqlite3_stmt *stmt;
    int result;
    sprintf(query, "INSERT INTO route (id, pthid, csid, nsid, ordnum) VALUES (NULL, %d, %d, %d, %d)",  Route.pathid, Route.currentstopid, Route.nextstopid, Route.ordernumber);
    result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error al preparar el query (INSERT)\n");
    }
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al añadir ruta\n");
    } else {
        printf("Ruta añadida correctamente\n");
    }
    logAppendDB(db, query, result);
    free(query);
    sqlite3_finalize(stmt);
}

int rtcrtrscr(sqlite3 *db) {
    int res = 0;
    int flg0 = 0;
    int flg1 = 0;
    int qPathid;
    int qCurrentStopId;
    int qNextStopId;
    int qOrderNumber;
    char* buffer = malloc(sizeof(char) * 2);
    char* qBuf = malloc(sizeof(char) * 10);

    while (flg0 < 1) {
        fflush(stdin);
        system("CLS");
        printf("[Creacion de Ruta]\n\nIntroduzca un numero de ruta valido\n\n");
        fgets(qBuf, 10, stdin);
        sscanf(qBuf, "%d", &qPathid);
        if (qPathid < 0) {
            fflush(stdin);
            printf("Numero Invalido;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
            getch();
        } else {
            fflush(stdin);
            flg0++;
        }
    }
    flg0--;

    while (flg1 < 1) {
        fflush(stdin);
        system("CLS");
        printf("[Creacion de Ruta]\n\nIntroduzca una parada actual valida\n\n");
        fgets(qBuf, 10, stdin);
        sscanf(qBuf, "%d", &qCurrentStopId);
        if (qCurrentStopId < 0) {
            fflush(stdin);
            printf("Parada Invalida;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
            getch();
        } else {
            fflush(stdin);
            flg1++;
        }
    }
    flg1--;

    while (flg0 < 1) {
        fflush(stdin);
        system("CLS");
        printf("[Creacion de Ruta]\n\nIntroduzca una siguiente parada valida\n\n");
        fgets(qBuf, 10, stdin);
        sscanf(qBuf, "%d", &qNextStopId);
        if (qNextStopId < 0) {
            fflush(stdin);
            printf("Parada Invalida;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
            getch();
        } else {
            fflush(stdin);
            flg0++;
        }
    }
    flg0--;

    while (flg1 < 1) {
        fflush(stdin);
        system("CLS");
        printf("[Creacion de Ruta]\n\nIntroduzca un numero de orden valido\n\n");
        fgets(qBuf, 10, stdin);
        sscanf(qBuf, "%d", &qOrderNumber);
        if (qOrderNumber < 0) {
            fflush(stdin);
            printf("Numero Invalido;\nPor favor, introduzca un numero valido\n[PRESIONE CUALQUIER TECLA PARA CONTINUAR]\n");
            getch();
        } else {
            fflush(stdin);
            flg1++;
        }
    }
    flg1--;

    Route qRoute = creaRoute(qPathid, qCurrentStopId, qNextStopId, qOrderNumber);
    anyadirRoute(db, qRoute);
    printf("[Creacion de Ruta]\n\nFuncion Finalizada\nPulse cualquier tecla para continuar\n");
    getch();

    while (flg0 == 0) {
        system("CLS");
        printf("Quiere anyadir otra Ruta? (1/0)\n");
        fgets(buffer, 2, stdin);
        sscanf(buffer, "%d", &res);
        if (res == 1 || res == 0)
            flg0++;
        else {
            printf("[Creacion de Ruta]\n\nInput Erroneo.\nPresione cualquier tecla para volver a intentar.\n");
            getch();
        }
    }

    free(buffer);
    free(qBuf);
    return res;
}

void visualizarRutas(sqlite3 *db) {
    int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
    int result;
    char* query = malloc(sizeof(char) * 128);
    sprintf(query, "SELECT MAX(id) FROM Route");
    char* query2;
    int qId;
    int qPathid;
    int qCurrentStopId;
    int qNextStopId;
    int qOrderNumber;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
    result = sqlite3_step(stmt);
    free(query);
    numR = sqlite3_column_int(stmt, 0); //Numero de Rutas: perfecto
    system("CLS");
    printf("[LISTA DE RUTAS]\n\n");
    for (int i = 0; i <= numR; i++) {
        query2 = malloc(sizeof(char) * 128);
        sprintf(query2, "SELECT * FROM Route where id = %d", i);
        sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            qId = sqlite3_column_int(stmt, 0);
            qPathid = sqlite3_column_int(stmt, 1);
            qCurrentStopId = sqlite3_column_int(stmt, 2);
            qNextStopId = sqlite3_column_int(stmt, 3);
            qOrderNumber = sqlite3_column_int(stmt, 4);
            printf("[ID] %d [PathID] %d [CurrentStopID] %d [NextStopID] %d [OrderNumber] %d\n",
                   qId, qPathid, qCurrentStopId, qNextStopId, qOrderNumber);
        }
        free(query2);
    }
    sqlite3_finalize(stmt);
    printf("\n\n[PRESIONAR CUALQUIER TECLA PARA CONTINUAR]");
    getch();
}

void imprimirRutas(sqlite3 *db) {
    int numR; //Numero de filas. Truco: SELECT Count(*) FROM tblName
    FILE* f;
    f = fopen("Rutas.txt", "w");
    int result;
    char* query = malloc(sizeof(char) * 128);
    sprintf(query, "SELECT MAX(id) FROM Route");
    char* query2;
    int qId;
    int qPathid;
    int qCurrentStopId;
    int qNextStopId;
    int qOrderNumber;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
    result = sqlite3_step(stmt);
    free(query);
    numR = sqlite3_column_int(stmt, 0); //Numero de Rutas: perfecto
    system("CLS");
    printf("[IMPRIMIENDO RUTAS]\n\n");
    for (int i = numR; i > 0; i--) {
        query2 = malloc(sizeof(char) * 128);
        sprintf(query2, "SELECT * FROM Route where id = %d", i);
        sqlite3_prepare_v2(db, query2, strlen(query2), &stmt, NULL);
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            qId = sqlite3_column_int(stmt, 0);
            qPathid = sqlite3_column_int(stmt, 1);
            qCurrentStopId = sqlite3_column_int(stmt, 2);
            qNextStopId = sqlite3_column_int(stmt, 3);
            qOrderNumber = sqlite3_column_int(stmt, 4);
            fprintf(f, "[ID] %d [PathID] %d [CurrentStopID] %d [NextStopID] %d [OrderNumber] %d\n",
                    qId, qPathid, qCurrentStopId, qNextStopId, qOrderNumber);
        }
        free(query2);
    }
    fclose(f);
    sqlite3_finalize(stmt);
    printf("\n\n[RUTAS IMPRESAS, PULSE CUALQUIER TECLA PARA CONTINUAR]");
    getch();
}
