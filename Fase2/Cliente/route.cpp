#include "route.h"
#include <iostream>

using namespace std;


Route::Route() {
	id = 0;
	pathid = 0;
	currentstopid = 0;
	nextstopid = 0;
	ordernumber = 0;
}

Route::Route(int id, int pathid, int currentstopid, int nextstopid, int ordernumber) {
	this->id = id;
	this->pathid = pathid;
	this->currentstopid = currentstopid;
	this->nextstopid = nextstopid;
	this->ordernumber = ordernumber;
}

int Route::getId() const {
	return id;
}

int Route::getPathId() const {
	return pathid;
}

int Route::getCurrentStopId() const {
	return currentstopid;
}

int Route::getNextStopId() const {
	return nextstopid;
}

int Route::getOrderNumber() const {
	return ordernumber;
}

void Route::setId(int id) {
	this->id = id;
}

void Route::setPathId(int pathid) {
	this->pathid = pathid;
}

void Route::setCurrentStopId(int currentstopid) {
	this->currentstopid = currentstopid;
}

void Route::setNextStopId(int nextstopid) {
	this->nextstopid = nextstopid;
}

void Route::setOrderNumber(int ordernumber) {
	this->ordernumber = ordernumber;
}

Route::~Route() {

}

void Route::imprimirRoute() const {
	cout<<"Route ID: "<<id<<endl;
	cout<<"Path ID: "<<pathid<<endl;
	cout<<"Current Stop ID: "<<currentstopid<<endl;
	cout<<"Next Stop ID: "<<nextstopid<<endl;
	cout<<"Order Number: "<<ordernumber<<endl;
}
