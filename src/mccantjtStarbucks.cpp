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
	Entry* starbucks=new Entry[n];
	for(int i=0; i<n; ++i){
		starbucks[i]=c[i];
	}
	size=n;
}

Entry* mccantjtStarbucks::getNearest(double x, double y){
	double distance=sqrt((x-starbucks[0].x)*(x-starbucks[0].x) + (y-starbucks[0].y)*(y-starbucks[0].y));
	Entry* nearest= &(starbucks[0]);
	for(int i=1; i<size; ++i){
		double distance2=sqrt((x-starbucks[i].x)*(x-starbucks[i].x) + (y-starbucks[i].y)*(y-starbucks[i].y));
		if(distance2<distance){
			distance=distance2;
			nearest=&(starbucks[i]);
		}
	}
	return nearest;
}

