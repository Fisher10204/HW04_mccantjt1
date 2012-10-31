#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "mccantjtStarbucks.h"
#include <fstream>
#include <cstdlib>
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

mccantjtStarbucks::mccantjtStarbucks(){

}
//Currently builds with all starbucks, needs to be modified to exclude starbucks that are too close, see Starbucks.h
void mccantjtStarbucks::build(Entry* c, int n){
	starbucks=new Entry[n];
	for(int i=0; i<n; ++i){
		starbucks[i]=c[i];
	}
	size=n;
}

Entry* mccantjtStarbucks::getNearest(double x, double y){
	double distance=sqrt((x-starbucks[0]->getX())*(x-starbucks[0]->getX()) + (y-starbucks[0]->getY())*(y-starbucks[0]->getY()));
	Entry* nearest= &(starbucks[0]);
	for(int i=1; i<size; ++i){
		double distance2=sqrt((x-starbucks[i]->getX())*(x-starbucks[i]->getX()) + (y-starbucks[i]->getY())*(y-starbucks[i]->getY()));
		if(distance2<distance){
			distance=distance2;
			nearest=&(starbucks[i]);
		}
	}
	return nearest;
}

