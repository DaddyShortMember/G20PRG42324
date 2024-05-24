#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "stop.h"

using namespace std;



Stop::Stop(int id, string name){
	this->id=id;
	this->name=name;
};

Stop::~Stop(){

};

int Stop::getId(){
	return id;
};
void Stop::setId(int id){
	this->id=id;
};
string Stop::getName(){
	return name;
};
void Stop::setName(string name){
	this->name=name;
}
void Stop::printStop(Stop s){
	cout << "Id de parada: " << s.getId() << endl;
	cout << "Nombre de parada: " << s.getName() << endl;
}



