#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "mccantjtStarbucks.h"
#include "cinder/Rand.h"
#include <fstream>
#include <cstdlib>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	Entry* readInFile();
};

Entry* HW04App::readInFile(){
	string line;
	double x,y;
	ifstream myFile("Starbucks_2006.csv");
	int sizeOfFile=7655;

	Entry* arr=new Entry[sizeOfFile];
	for(int i=0; i<sizeOfFile; ++i){
			getline(myFile, line, ',');
			arr[i].identifier = line;
			getline(myFile, line, ',');
			x = atof(line.c_str());
			arr[i].x = x;
			getline(myFile, line, '\r');
			y = atof(line.c_str());
			arr[i].y = y;
	}
	return arr;
}

void HW04App::setup()
{
	mccantjtStarbucks* myDataType=new mccantjtStarbucks();
	Entry* myStarbucks=readInFile();
	Entry* nearestLoc;

	myDataType->build(myStarbucks, 7655);
	nearestLoc=myDataType->getNearest(.3,.3);
	HW04App::console() << nearestLoc->identifier << std::endl;
}

void HW04App::mouseDown( MouseEvent event )
{
}

void HW04App::update()
{
}

void HW04App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04App, RendererGl )
