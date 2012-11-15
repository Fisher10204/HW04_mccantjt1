// Jacob McCanty

#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Starbucks.h"
#include "mccantjtStarbucks.h"
#include "Entry.h"
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
	Entry* readIn2000(int* intArr);
	Entry* readIn2010(int* intArr);
	Entry* nearestLoc;
	mccantjtStarbucks* myDataType;
	void drawStarbucks(uint8_t* surfacePixels, Entry* entries);
	//will be used to draw locations of starbucks, as well as locations from the census data
	void drawPoint(uint8_t* surfacePixels, int x, int y, int red, int green, int blue);
	//this method will come in handy when highlighting starbucks because we won't have to loop through the entire array
	void drawIndividualStarbucks(uint8_t surfacePixels, Entry* starbucks);
	void drawMap(uint8_t* surface, uint8_t* image);
	void drawCensusData(int* intArr1, int* intArr2, Entry* firstCensus, Entry* secondCensus, uint8_t* surfacePixels);
private:
	Surface* mySurface;
	static const int appWidth=650;
	static const int appHeight=500;
	static const int surfaceSize=1024;

	int* intArr2000;
	int* intArr2010;
	
	//gl::Texture usPic;
	Surface* usPic;
	uint8_t* pixels;
	uint8_t* imagePixels;
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
			arr[i].identifier= line;
			getline(myFile, line, ',');
			x = atof(line.c_str());
			arr[i].x = x;
			getline(myFile, line, '\r');
			y = atof(line.c_str());
			arr[i].y = 1.0-y;
	}
	cout <<"read in file"<<endl;
	myFile.close();
	return arr;
}
//the intArr in readIn2000 and 2010 are used to store the population values for given areas, had some trouble using my mccantjtEntry.cpp instead for some reason
Entry* HW04App::readIn2000(int* intArr){
	string line;
	double x,y;
	string stateID, countyID, censusID, groupID;
	int population;
	ifstream myFile("Census_2000.csv");
	int sizeOfFile=206676;
	myFile.open("../resources/Census_2000.csv");
	Entry* arr=new Entry[sizeOfFile];
	for(int i=0; i<sizeOfFile; ++i){
			getline(myFile, line, ',');
			stateID=line;
			getline(myFile, line, ',');
			countyID=line;
			getline(myFile, line, ',');
			censusID=line;
			getline(myFile, line, ',');
			groupID=line;
			arr[i].identifier= stateID+", "+countyID+", "+censusID+", "+groupID;
			getline(myFile, line, ',');
			intArr[i]= (int)atof(line.c_str());
			getline(myFile, line, ',');
			x = atof(line.c_str());
			arr[i].x = x;
			getline(myFile, line, '\r');
			y = atof(line.c_str());
			arr[i].y = 1.0-y;
	}
	cout <<"read in file"<<endl;
	myFile.close();
	return arr;
}

Entry* HW04App::readIn2010(int* intArr){
	string line;
	double x,y;
	string stateID, countyID, censusID, groupID;
	int population;
	ifstream myFile("Census_2010.csv");
	int sizeOfFile=216331;
	myFile.open("../resources/Census_2010.csv");
	Entry* arr=new Entry[sizeOfFile];
	for(int i=0; i<sizeOfFile; ++i){
			getline(myFile, line, ',');
			stateID=line;
			getline(myFile, line, ',');
			countyID=line;
			getline(myFile, line, ',');
			censusID=line;
			getline(myFile, line, ',');
			groupID=line;
			arr[i].identifier= stateID+", "+countyID+", "+censusID+", "+groupID;
			getline(myFile, line, ',');
			intArr[i]= (int)atof(line.c_str());
			getline(myFile, line, ',');
			x = atof(line.c_str());
			arr[i].x = x;
			getline(myFile, line, '\r');
			y = atof(line.c_str());
			arr[i].y = 1.0-y;
	}
	cout <<"read in file"<<endl;
	myFile.close();
	return arr;
}


void HW04App::drawMap(uint8_t* surface, uint8_t* image)	{
	int offset, offset_image;
	for (int j = 0; j < appHeight; j++)	{
		for(int i = 0; i < appWidth; i++)	{
			offset = 3*(i + j*surfaceSize);
			offset_image = 3*(i + j*appWidth);
			surface[offset + 0] = image[offset_image + 0];
			surface[offset + 1] = image[offset_image + 1];
			surface[offset + 2] = image[offset_image + 2];
		}
	}
}

void HW04App::setup()
{
	mySurface=new Surface(surfaceSize,surfaceSize,false);
	usPic=new Surface(loadImage(loadResource(RES_US_PIC, "IMAGE")));
	
	myDataType=new mccantjtStarbucks();
	Entry* myStarbucks=readInFile();
	nearestLoc=new Entry();
	pixels = (*mySurface).getData();
	imagePixels= (*usPic).getData();
	drawMap(pixels,imagePixels);
	intArr2000=new int[206676];
	intArr2010=new int[216331];
	//read in then draw in census data to pixels here
	Entry* census2000=readIn2000(intArr2000);
	Entry* census2010=readIn2010(intArr2010);
	drawCensusData(intArr2000,intArr2010, census2000, census2010, imagePixels);
	//draw in starbucks locations to pixels here
	drawStarbucks(imagePixels,myStarbucks);
	myDataType->build(myStarbucks, 7655);
	nearestLoc=myDataType->getNearest(.75,.25);
	HW04App::console() << nearestLoc->identifier << std::endl;
}
//draws the starbucks locations as blue points on the map
void HW04App::drawStarbucks(uint8_t* surfacePixels, Entry* entries)
{
	for(int i=0; i<7655; ++i){
		drawPoint(surfacePixels,entries[i].x*800, entries[i].y*600, 0, 0, 150);
	}
}
//compares the populations of the smaller census data to that of the larger and colors the points accordingly
//once the smaller census(the first one) has reached the end of its data all the remaining points from the second census will be colored green
void HW04App::drawCensusData(int* intArr1, int* intArr2, Entry* firstCensus, Entry* secondCensus, uint8_t* surfacePixels){
	for(int i=0; i<216331; ++i)
	{
		if(i<206676)
		{
			int popDiff=intArr1[i]-intArr2[i];
			//population has increased, color green
			if(popDiff<=0)
			{
				popDiff=popDiff*(-1);
				//divide by previous pop (intArr1) to get the percentage difference
				double percentChange=((double)popDiff)/((double)intArr1[i]);
				drawPoint(surfacePixels,secondCensus[i].x*800, secondCensus[i].y*600, 0, 255*percentChange,0);
			}
			//popDiff>0, population has decreased, color red
			else
			{
				double percentChange=((double)popDiff)/((double)intArr1[i]);
				drawPoint(surfacePixels, secondCensus[i].x*800, secondCensus[i].y*600,255*percentChange,0,0);
			}
		}
		//whatever points remain are population increases, and thus fully green
		else
		{
			drawPoint(surfacePixels, secondCensus[i].x*800, secondCensus[i].y*600,0,255,0);
		}
	}
}

void HW04App::drawPoint(uint8_t* surfacePixels, int x, int y, int red, int green, int blue){
	int offset=3*(x+y*600);
	surfacePixels [offset]=red;
	surfacePixels [offset+1]=green;
	surfacePixels [offset+2]=blue;
}

void HW04App::mouseDown( MouseEvent event )
{
	if(event.isLeft())
	{
		double mouseX=((double)event.getX())/((double)getWindowBounds().getWidth());
		double mouseY=((double)event.getY())/((double)getWindowBounds().getHeight());
		nearestLoc=myDataType->getNearest(mouseX,mouseY);
		//I have my click printing out the starbucks it is supposed to be closest to in the console because I have no real way og highlighting an individual point
		HW04App::console() << nearestLoc->identifier << std::endl;
	}
}

void HW04App::update()
{
}

void HW04App::draw()
{
	// draw the image of the USA
	gl::draw(*usPic,Area(-20,-50,660,500));
	//gl::draw(usPic,Area(0,0,650,500));
	//gl::draw(*usPic, getWindowBounds());
}

CINDER_APP_BASIC( HW04App, RendererGl )
