#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
#ifndef USER_H_
#define USER_H_


class User{

	private:
	int id;
	string name;
	string mail;
	string pass;
	int auth; // 1 - Administrador 2 - Usuario especial 3 - Usuario normal

	public:
	User();
	User(int id,string name, string mail, string pass);
	~User();
	int getId();
	void setId(int id);
	string getNombre();
	void setNombre(string name);
	string getMail();
	void setMail(string mail);
	string getPass();
	void setPass(string pass);
	void printUser(User u);

};



#endif /* USER_H_ */
