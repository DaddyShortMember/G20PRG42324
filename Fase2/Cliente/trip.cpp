#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "trip.h"

using namespace std;


	Trip::Trip(int id, int busid, int pathid,string etime, string atime, int price){
		this->id=id;
		this->busid=busid;
		this->pathid=pathid;
		this->etime=etime;
		this->atime=atime;
		this->price=price;
	};

	Trip::~Trip(){
	};

	int Trip::getId(){
		return id;
	};
	void Trip::setId(int id){
		this->id=id;
	};
	int Trip::getBusid(){
		return busid;
	};
	void Trip::setBusid(int busid){
		this->busid=busid;
	};
	int Trip::getPathid(){
		return pathid;
	};
	void Trip::setPathid(int pathid){
		this->pathid=pathid;
	};
	string Trip::getEtime(){
		return etime;
	};
	void Trip::setEtime(string etime){
		this->etime=etime;
	};
	string Trip::getAtime(){
		return atime;
	}
	void Trip::setAtime(string atime){
		this->atime=atime;
	}
	int Trip::getPrice(){
		return price;
	};
	void Trip::setPrice(int price){
		this->price=price;
	};
	void Trip::printTrip(Trip t){
		cout << "Id del Viaje: " << t.getId() << endl;
		cout << "ID del Bus: " << t.getBusid() << endl;
		cout << "ID del Recorrido: " << t.getPathid() << endl;
		cout << "Hora de salida: " << t.getEtime() << endl;
		cout << "Hora de llegada: " << t.getAtime() << endl;
		cout << "Precio del viaje: " << t.getPrice() << endl;
	};






