#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "ticket.h"

using namespace std;

	Ticket::Ticket(int id,int usid,int tripid,string date){
		this->id=id;
		this->usid = usid;
		this->tripid=tripid;
		this->date=date;
	};
	Ticket::~Ticket(){

	};
	int Ticket::getId(){
		return id;
	};
	void Ticket::setId(int id){
		this->id=id;
	};
	int Ticket::getUsid(){
		return usid;
	};
	void Ticket::setUsid(int usid){
		this->usid=usid;
	};
	int Ticket::getTripid(){
		return tripid;
	};
	void Ticket::setTripid(int tripid){
		this->tripid=tripid;
	};
	string Ticket::getDate(){
		return date;
	}
	void Ticket::setDate(string date){
		this->date=date;
	}
	void printTicket(Ticket t){
		cout << "ID del ticket: " << t.getId() << endl;
		cout << "ID del usuario: " << t.getUsid() << endl;
		cout << "ID del viaje: " << t.getTripid() << endl;
		cout << "Fecha del ticket: " << t.getDate() << endl;
	};




