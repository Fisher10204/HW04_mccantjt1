// Jacob McCanty

#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Starbucks.h"
#include "mccantjtStarbucks.h"
#include "Resources.h"
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
private:
	Surface* mySurface;
	static const int appWidth=800;
	static const int appHeight=800;
	static const int surfaceSize=1024;
	void drawImage(uint8_t* surface, uint8_t* image);
	gl::Texture usPic;
};

Entry* HW04App::readInFile(){
	string line;
	double x,y;
	ifstream myFile("Starbucks_2006.csv");
	int sizeOfFile=7655;
	myFile.open("../resources/Starbucks_2006.csv");
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
	cout <<"read in file"<<endl;
	myFile.close();
	return arr;
}

void HW04App::setup()
{
	mySurface=new Surface(surfaceSize,surfaceSize,false);
	usPic=gl::Texture(loadImage(loadResource(RES_US_PIC, "IMAGE")));
	
	mccantjtStarbucks* myDataType=new mccantjtStarbucks();
	Entry* myStarbucks=readInFile();
	Entry* nearestLoc=new Entry();

	myDataType->build(myStarbucks, 7655);
	nearestLoc=myDataType->getNearest(.75,.25);
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
	gl::draw(usPic,getWindowBounds());
}

CINDER_APP_BASIC( HW04App, RendererGl )
