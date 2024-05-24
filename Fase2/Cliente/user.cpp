#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "user.h"

using namespace std;



User::User(){
	id=0;
	mail="null";
	name="null";
	pass="null";
	auth=3;
};

User::User(int id,string name, string mail, string pass){
	this->id=id;
	this->mail=mail;
	this->name = name;
	this->pass=pass;
	auth=3;
};

User::~User(){
};

int User::getId()
{
	return id;
};
void User::setId(int id)
{
	this->id = id;
};
string User::getNombre()
{
	return name;
};
void User::setNombre(string name)
{
	this->name = name;
};
string User::getMail()
{
	return mail;
};
void User::setMail(string mail)
{
	this->mail = mail;
};
string User::getPass()
{
	return pass;
};
void User::setPass(string pass)
{
	this->pass = pass;
};

void User::printUser(User u)
{
	cout << "Id del usuario: " << u.getId() << endl;
	cout << "Nombre del usuario: " << u.getNombre() << endl;
	cout << "Email del usuario: " << u.getMail() << endl;
	cout << "Contrasenya  del usuario: " << u.getPass() << endl;
};






