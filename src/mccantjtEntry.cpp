#pragma once
#include "Entry.h"
#include <string>
using namespace std;

mccantjtEntry::mccantjtEntry(){
	x=-1.0;
	y=-1.0;
	name="";
}

mccantjtEntry::mccantjtEntry(string new_name, double x2, double y2){
	x=x2;
	y=y2;
	name=new_name;
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