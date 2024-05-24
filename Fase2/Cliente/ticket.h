#include <iostream>
#include <string>
using namespace std;

#ifndef TICKET_H_
#define TICKET_H_



class Ticket{

private:
	int id;
	int usid;
	int tripid;
	string date;

public:
	Ticket(int id,int usid,int tripid,string date);
	~Ticket();
	int getId();
	void setId(int id);
	int getUsid();
	void setUsid(int usid);
	int getTripid();
	void setTripid(int tripid);
	string getDate();
	void setDate(string date);
	void printTicket(Ticket t);

};





#endif /* TICKET_H_ */
