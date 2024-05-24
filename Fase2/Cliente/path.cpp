#include "path.h"
#include <iostream>

using namespace std;

Path::Path() {
	id = 0;
	initialstop = 0;
	finalstop = 0;
}

Path::Path(int id, int initialstop, int finalstop) {
	this->id = id;
	this->initialstop = initialstop;
	this->finalstop = finalstop;
}

int Path::getId() const {
	return id;
}

int Path::getInitialStop() const {
	return initialstop;
}

int Path::getFinalStop() const {
	return finalstop;
}

void Path::setId(int id) {
	this->id = id;
}

void Path::setInitialStop(int initialstop) {
	this->initialstop = initialstop;
}

void Path::setFinalStop(int finalstop) {
	this->finalstop = finalstop;
}

Path::~Path() {

}

void Path::imprimirPath() {
	cout<<"Path ID: "<< id<<endl;
	cout<<"Initial Stop: "<<initialstop<<endl;
	cout<<"Final Stop: "<<finalstop<<endl;
}
