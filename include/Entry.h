//Jacob McCanty

#pragma once
#include "Starbucks.h"
#include <string>
using namespace std;

class mccantjtEntry : public Entry{
public:
	mccantjtEntry();
	mccantjtEntry(int stateID2, int countyID2, int censusID2, int groupID2, int population2, double x2, double y2);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	void setName(string name);
	string getName();
	//only to be used for census data
	void setState(int ID);
	int getState();
	void setCounty(int ID);
	int getCounty();
	void setCensus(int ID);
	int getCensus();
	void setGroup(int ID);
	int getGroup();
	void setPopulation(int population);
	int getPopulation();
private:
	string name;
	double x;
	double y;
	//this info will only be used for census data
	int stateID;
	int countyID;
	int censusID;
	int groupID;
	int population;
};