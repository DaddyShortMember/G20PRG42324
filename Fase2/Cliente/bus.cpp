#include <iostream>
#include <cstring>

#include "bus.h"

using namespace std;

Bus::Bus() {
	id = 0;
	strcpy(license, "");
	seats = 0;
}

Bus::Bus(int id, const char* license, int seats) {
    this->id = id;
    strncpy(this->license, license, sizeof(this->license) - 1);
    this->license[sizeof(this->license) - 1] = '\0';
    this->seats = seats;
}

int Bus::getId() const {
    return id;
}

const char* Bus::getLicense() const {
    return license;
}

int Bus::getSeats() const {
    return seats;
}

void Bus::setId(int id) {
    this->id = id;
}

void Bus::setLicense(const char* license) {
    strncpy(this->license, license, sizeof(this->license) - 1);
    this->license[sizeof(this->license) - 1] = '\0';
}

void Bus::setSeats(int seats) {
    this->seats = seats;
}

Bus::~Bus() {
}


void Bus::imprimirBus() {
    cout<<"Bus ID: "<<id<<endl;
    cout<<"License: "<<license<<endl;
    cout<<"Seats: "<<seats<<endl;
}
