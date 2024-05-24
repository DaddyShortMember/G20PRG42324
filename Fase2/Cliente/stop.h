#include <iostream>
#include <string>
using namespace std;

#ifndef STOP_H_
#define STOP_H_


class Stop{
private:
	int id;
	string name;
public:
	Stop(int id, string name);
	~Stop();
	int getId();
	void setId(int id);
	string getName();
	void setName(string name);
	void printStop(Stop s);
};


#endif /* STOP_H_ */
