#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <winsock2.h>
#include "user.h"
#include "path.h"
#include "route.h"
#include "stop.h"
#include "bus.h"
#include "sqlite3.h"
#include "trip.h" 
#include "logger.h"
#include "ticket.h"



#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

//Funciones para clientes y administracion

/*
int sendTripData(void);
int sendUserData(void);
int sendTicketData(void);
int ticketPurchase(void);
int registerUser(void);
//Funciones para administracion
int sendBusData(void);
int registerBus(void);
int sendRouteData(void);
int registerRoute(void);
int sendStopData(void);
int registerStop(void);
int sendPathData(void);
int registerPath(void);
int registerTrip(void);
*/
 //TODO:
 //*Programar funciones de servidor.

int main(void)
{
	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	sqlite3 *db;
	sqlite3_open("DB.db", &db);
	logOpen(db);

	char usr;
	char pss;
	char mil;
	char qry;
	int flg = 1;

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	//TODO: USER, BUS, ROUTE, PATH, TRIP, TICKET
	printf("Waiting for incoming commands from client... \n");
	do
	{
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);

		printf("Command received: %s \n", recvBuff);
		//LOGIN
		if (strcmp(recvBuff, "50") == 0)
		{
			int flg = 0;
			int aut = -1;
			int xx = 0;
			printf("Enters\n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			while (flg >= 0)
			{
				printf("While iteration\n");
				printf("received: %s \n", recvBuff);
				if(flg == 0){
					mil = malloc(sizeof(char)*30);
					strcpy(mil,recvBuff);
					flg++;
				}
				if(flg == 1){
					pss = malloc(sizeof(char)*30);
					strcpy(pss,recvBuff);
					flg++;
				}
				int n = exists(db,mil);
				if(n == 1 && flg >= 1){
					xx = passCheck(db,mil,pss);
					flg = -1;
					}
				if(n == 0){
					flg = -1;
					aut = -1;
				}
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			}
			if(xx != 1)
				aut = -1;
			else{
				Usuario user = getUser(db,mil);
				aut = user.auth;
			}
			sprintf(sendBuff, "%d", aut);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Response sent: %s \n", sendBuff);
			free(mil);
			free(pss);
		}
		//Register
		if (strcmp(recvBuff, "49") == 0)
		{
			int flg = 0;
			int aut = 3;
			int xx = 0;
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			while (strcmp(recvBuff, "440") != 0 && flg >= 0)
			{
				if(flg == 0){
					mil = malloc(sizeof(char)*30);
					strcpy(mil,recvBuff);
					flg++;
				}
				if(flg == 1){
					pss = malloc(sizeof(char)*30);
					strcpy(pss,recvBuff);
					flg++;
				}
				if(flg == 2){
					usr = malloc(sizeof(char)*30);
					strcpy(pss,recvBuff);
					flg++;
				}
				int n = exists(db,mil);
				if(n == 1){
					flg = -1;
					aut =  -1;
				}
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			}
			Usuario us = creaUsuario(usr,mil,pss,aut);
			anyadirUsuario(db,us);
			sprintf(sendBuff, "%d", aut);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Response sent: %s \n", sendBuff);
			free(mil);
			free(pss);
			free(usr);
		}
		//Ticket List
		if (strcmp(recvBuff, "TICKETS") == 0)
		{
			Ticket ti;
			int ct = 0;
			int uId;
			char* qDat;
			int qTid;
			int qId;
			int qUsid;
			char dat[13];
			sqlite3_stmt *stmt;
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			uId = atoi(recvBuff);
			qry = malloc(sizeof(char)*128);
			sprintf(qry, "SELECT date('now')");
			sqlite3_prepare_v2(db, qry, strlen(qry), &stmt, NULL);
			sqlite3_step(stmt);
			strcpy(dat,sqlite3_column_text(stmt, 0));
			free(qry);
			qry = malloc(sizeof(char)*128);
			sprintf(qry, "SELECT count(*) FROM ticket where date = '%s' and usid = '%d'",dat,uId);
			sqlite3_prepare_v2(db, qry, strlen(qry), &stmt, NULL);
			sqlite3_step(stmt);
			ct = sqlite3_column_int(stmt, 0);
			free(qry);
			for(int dd = 0; dd < ct; dd++){
				qry = malloc(sizeof(char)*128);
				qDat = malloc(sizeof(char)*13);
				sprintf(qry, "SELECT * from ticket where date > '%s'",dat);
				sqlite3_prepare_v2(db, qry, strlen(qry), &stmt, NULL);
				sqlite3_step(stmt);
				qId = sqlite3_column_int(stmt, 0);
				qUsid = sqlite3_column_int(stmt, 1);
				qTid = sqlite3_column_int(stmt, 2);
				strcpy(qDat,sqlite3_column_text(stmt, 3));
				ti = creaTicket(qId,qTid,qDat);
				send(comm_socket, (char*)&ti, sizeof(sendBuff), 0);
				printf("Response sent: TICKET ID %d \n", ti.id);
				free(qry);
				free(qDat);
			}
			send(comm_socket, "DONE", sizeof(sendBuff), 0);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			if (strcmp(recvBuff, "TRIPSEE-END") == 0); // Nada que hacer
			printf("Response sent: %s \n", sendBuff);
		}
		//Ticket purchase
		if (strcmp(recvBuff, "TICKET") == 0)
		{
			Ticket* ti;
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			ti = (Ticket *)recvBuff;
			Ticket tix;
			strcpy(tix.date,ti->date);
			tix.usid = ti->usid;
			tix.tripid = ti->tripid;
			tix.id = ti->id;
			anyadirTicket(db,tix);
			if (strcmp(recvBuff, "TICKET-END") == 0); // Nada que hacer
			strcpy(sendBuff, inet_ntoa(server.sin_addr));
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Response sent: %s \n", sendBuff);
		}
		//Trip List
		if (strcmp(recvBuff, "TRIPSEE") == 0)
		{
			Trip tr;
			int ct = 0;
			char* qHs;
			char* qHl;
			int qBus;
    		int qPath;
			int qId;
			int qPrice;
			char tim[9];
			sqlite3_stmt *stmt;
			qry = malloc(sizeof(char)*128);
			sprintf(qry, "SELECT time('now')");
			sqlite3_prepare_v2(db, qry, strlen(qry), &stmt, NULL);
			sqlite3_step(stmt);
			strcpy(tim,sqlite3_column_text(stmt, 0));
			free(qry);
			qry = malloc(sizeof(char)*128);
			sprintf(qry, "SELECT count(*) FROM where etime > '%s'",tim);
			sqlite3_prepare_v2(db, qry, strlen(qry), &stmt, NULL);
			sqlite3_step(stmt);
			ct = sqlite3_column_int(stmt, 0);
			free(qry);
			for(int dd = 0; dd < ct; dd++){
				qry = malloc(sizeof(char)*128);
				qHs = malloc(sizeof(char)*8);
				qHl = malloc(sizeof(char)*8);
				sprintf(qry, "SELECT * from TRIP where etime > '%s'",tim);
				sqlite3_prepare_v2(db, qry, strlen(qry), &stmt, NULL);
				sqlite3_step(stmt);
				qId = sqlite3_column_int(stmt, 0);
				qBus = sqlite3_column_int(stmt, 1);
				qPath = sqlite3_column_int(stmt, 2);
				strcpy(qHs,sqlite3_column_text(stmt, 3));
				strcpy(qHl,sqlite3_column_text(stmt, 4));
				qPrice = sqlite3_column_int(stmt, 5);
				tr = creaTrip(qId,qBus,qHs,qHl,qPrice);
				send(comm_socket, (char*)&tr, sizeof(sendBuff), 0);
				printf("Response sent: TRIP ID %d \n", tr.id);
				free(qry);
				free(qHs);
				free(qHl);
			}
			//send(comm_socket, "DONE", sizeof(sendBuff), 0);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			if (strcmp(recvBuff, "TRIPSEE-END") == 0); // Nada que hacer
			printf("Response sent: %s \n", sendBuff);
		}

		if (strcmp(recvBuff, "EXIT") == 0)
			flg++;

	} while (flg == 1);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}