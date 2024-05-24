#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <string.h>
#include <cstdlib>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
using namespace std;

void limpiarPantalla() {
    system("cls");
}

char menu(){
	char opcion;
	cout<<"1. Registrarse"<<endl;
	cout<<"2. Iniciar Sesion"<<endl;
	cout<<"0. Salir"<<endl;
	cout<<"Elige una opcion: ";
	cin>>opcion;

	return opcion;
	//limpiarPantalla();
}

char menuCliente(){
	int opcionC;
	cout<<"MENU CLIENTE"<<endl;
	cout<<"1.Ver y reservar viajes "<<endl;
	cout<<"0. Salir"<<endl;
	cout<<"Elige una opcion: ";
	cin>>opcionC;
	return opcionC;
}

int main(int argc, char *argv[]) {

	char name[30],mail[30],pass[30];
	int resul,id,auth,nuevoPrecio,opcion,opcionA,opcionC,precio;
	int idRoute, idPath, idBus, idTrip;
	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	/*
	 * En sendBuff guardaremos lo que el cliente le envia al servidor
	 * En recvBuff guardaremos lo que el servidor le envia al cliente
	 * */
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	/*EMPIEZA EL PROGRAMA DEL CLIENTE*/

	do{
		opcion = menu();
		sprintf(sendBuff,"%d",opcion);
		send(s, sendBuff, sizeof(sendBuff), 0);



		switch(opcion){
		case '1':
			cout<<"====REGISTARSE===="<<endl;
			cout<<"EMAIL:";cin>>mail;
			cout<<"Password:";cin>>pass;
			cout<<"Nombre:";cin>>name;
			sprintf(sendBuff,"%s",mail);
			send(s, sendBuff, sizeof(sendBuff), 0);
			sprintf(sendBuff,"%s",pass);
			send(s, sendBuff, sizeof(sendBuff), 0);
			sprintf(sendBuff,"%s",name);
			send(s, sendBuff, sizeof(sendBuff), 0);
			sprintf(sendBuff,"%i",342);
			send(s, sendBuff, sizeof(sendBuff), 0);

			//limpiarPantalla();
			// Guardar datos del cliente en la base de datos

			break;
		case '2':
			cout<<"MAIL: ";cin>>mail;
			cout<<"CONTRASENYA: ";cin>>pass;

			sprintf(sendBuff,"%s",mail);
			send(s, sendBuff, sizeof(sendBuff), 0);
			sprintf(sendBuff,"%s",pass);
			send(s, sendBuff, sizeof(sendBuff), 0);

			recv(s, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff,"%d",&resul);
			sprintf(sendBuff,"%i",346);
			send(s, sendBuff, sizeof(sendBuff), 0);


			if(resul==1){
				do{
					opcionC = menuCliente();
					sprintf(sendBuff,"%d",opcionC);
					send(s, sendBuff, sizeof(sendBuff), 0);
					switch(opcionC){
						case 1:
						for(int j=0; j<sizeof(sendBuff);j++){
							cout << "Viaje" << idTrip << endl;
						}
						cout<<"ID del Viaje a reservar: ";cin>>idTrip;
						sprintf(sendBuff, "%d", idTrip);
						send(s, sendBuff, sizeof(sendBuff), 0);
						break;

						case 0: break;
						default: cout<<"La opcion no es correcta"<<endl;
					}
				}while(opcionC!=0);
			}else{
				cout<<"El Inicio de Sesion no ha sido correcto"<<endl;
			}
			break;
		case '0': cout<<"HASTA LA PROXIMA"<<endl;break;
		default: cout<<"La opcion seleccionada no es correcta"<<endl;

		}

	}while(opcion!='0');

	/*ACABA EL PROGRAMA DEL CLIENTE*/
	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
