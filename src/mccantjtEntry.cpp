//Jacob McCanty

#pragma once
#include "Entry.h"
#include <string>
using namespace std;

mccantjtEntry::mccantjtEntry(){
	x=-1.0;
	y=-1.0;
	name="";
}
//use for census info
mccantjtEntry::mccantjtEntry(int stateID2, int countyID2, int censusID2, int groupID2, int population2, double x2, double y2){
	x=x2;
	y=y2;
	stateID=stateID2;
	countyID=countyID2;
	censusID=censusID2;
	groupID=groupID2;
	population=population2;
}

double mccantjtEntry::getX()
{
	return x;
}

double mccantjtEntry::getY()
{
	return y;
}

string mccantjtEntry::getName()
{
	return name;
}

void mccantjtEntry::setName(string new_name)
{
	name=new_name;
}

void mccantjtEntry::setX(double x2)
{
	x=x2;
}
void mccantjtEntry::setY(double y2)
{
	y=y2;
}