#pragma once
#include "Starbucks.h"
#include <string>
using namespace std;

class mccantjtEntry : public Entry{
public:
	mccantjtEntry();
	mccantjtEntry(string name, double x, double y);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	void setName(string name);
	string getName();
private:
	string name;
	double x;
	double y;
};