#include "ticket.h"

Ticket getTicket(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    Ticket ticket;
    int result;
    char* query = malloc(sizeof(char)*1028);
    sprintf(query, "SELECT * FROM Ticket WHERE id = %d", id);
    sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
    result = sqlite3_step(stmt);
    free(query);
    if (result == SQLITE_ROW) {
        ticket.id = sqlite3_column_int(stmt, 0);
        ticket.usid = sqlite3_column_int(stmt, 1);
        ticket.tripid = sqlite3_column_int(stmt, 2);
        strcpy(ticket.date, sqlite3_column_text(stmt, 3));
    } else {
        printf("Ticket con ID %d no encontrado.\n", id);
        ticket.id = 0;
    }
    sqlite3_finalize(stmt);
    return ticket;
}

Ticket creaTicket(int usid, int tripid, const char *date) {
    Ticket ticket;
    ticket.usid = usid;
    ticket.tripid = tripid;
    strcpy(ticket.date, date);
    return ticket;
}

void anyadirTicket(sqlite3 *db, Ticket ticket) {
    char* query = malloc(sizeof(char)*256);
    sqlite3_stmt *stmt;
    int result;
    sprintf(query, "INSERT INTO Ticket (usid, tripid, date) VALUES (%d, %d, '%s')", ticket.usid, ticket.tripid, ticket.date);
    result = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error al preparar el query (INSERT)\n");
    }
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al introducir ticket\n");
    } else {
        printf("Ticket introducido\n");
    }
    free(query);
    sqlite3_finalize(stmt);
}
