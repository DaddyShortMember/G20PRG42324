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

		if (strcmp(recvBuff, "LOGIN") == 0)
		{
			int flg = 0;
			int aut = -1;
			int xx = 0;
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			while (strcmp(recvBuff, "LOGIN-END") != 0 && flg >= 0)
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
				//exists(db,mil);
				int n = exists(db,mil);
				if(n == 1 && flg >= 1)
					xx = passCheck(db,mil,pss);
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

		if (strcmp(recvBuff, "REGISTER") == 0)
		{
			int flg = 0;
			int aut = 3;
			int xx = 0;
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			while (strcmp(recvBuff, "REGISTER-END") != 0 && flg >= 0)
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
				if(n == 1)
					flg = -1;
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

		if (strcmp(recvBuff, "TICKETS") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			if (strcmp(recvBuff, "TICKETS-END") == 0); // Nada que hacer

			strcpy(sendBuff, inet_ntoa(server.sin_addr));
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Response sent: %s \n", sendBuff);
		}

		if (strcmp(recvBuff, "TICKET") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			if (strcmp(recvBuff, "TICKET-END") == 0); // Nada que hacer

			strcpy(sendBuff, inet_ntoa(server.sin_addr));
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Response sent: %s \n", sendBuff);
		}

		if (strcmp(recvBuff, "TRIPSEE") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			if (strcmp(recvBuff, "TRIPSEE-END") == 0); // Nada que hacer

			strcpy(sendBuff, inet_ntoa(server.sin_addr));
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
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