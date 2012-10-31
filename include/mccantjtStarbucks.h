//Jacob McCanty

#pragma once
#include "Starbucks.h"
using namespace std;

class mccantjtStarbucks : public Starbucks{
public:
	mccantjtStarbucks();
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Entry* starbucks;
	int size;
};