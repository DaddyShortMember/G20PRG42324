#include <iostream>
#include <string>
using namespace std;

#ifndef TRIP_H_
#define TRIP_H_


class Trip{
private:
	int id;
	int busid;
	int pathid;
	string etime;
	string atime;
	int price;
public:
	Trip(int id, int busid, int pathid,string etime, string atime, int price);
	~Trip();
	int getId();
	void setId(int id);
	int getBusid();
	void setBusid(int busid);
	int getPathid();
	void setPathid(int pathid);
	string getEtime();
	void setEtime(string etime);
	string getAtime();
	void setAtime(string atime);
	int getPrice();
	void setPrice(int price);
	void printTrip(Trip t);

};




#endif /* TRIP_H_ */
