#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"
#include <cstdlib> 
#include <iostream>
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class MarkusHW01App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void setPixel(uint8_t* ar, int x,int y, Color8u c);
	void drawRect(uint8_t* ar, int x,int y, int w, int h, Color8u c);
	void drawCirc(uint8_t* ar, int x,int y, double r, Color8u c);
	void drawLine(uint8_t* ar, int x, int y, int x2, int y2, Color8u c);

  private:
	float color1;
	float color2;
	float color3;
	int iteration;
	Surface* mySurface_;
	uint8_t* pixelArray;
	int width;
	float a;

};


void MarkusHW01App::setup()
{
	color1 = 1.0;
	color2 = 1.0;
	color3 = 1.0;
	iteration = 0;
	width = 640;

	mySurface_ = new Surface(1024,1024,false);
};

void MarkusHW01App::mouseDown( MouseEvent event )
{
};

void MarkusHW01App::setPixel(uint8_t* ar, int x,int y, Color8u c)
{
	ar[y * 1024 * 3 + 3 * x] = c.r;
	ar[y * 1024 * 3 + 3 * x + 1] = c.g;
	ar[y * 1024 * 3 + 3 * x + 2] = c.b;

};

void MarkusHW01App::drawRect(uint8_t* ar, int x,int y, int w, int h, Color8u c)
{
	for(int i = x; i < x + w; i++){
		for(int j = y; j < y + h; j++){
			setPixel(ar, i, j, c);
		};
	};

};

void MarkusHW01App::drawCirc(uint8_t* ar, int x,int y, double r, Color8u c)
{

	for(double i = 0; i < 360; i = i + .01){
		setPixel(ar, cos(i) * r + x, sin(i) * r + y, c);
	};

};

void MarkusHW01App::drawLine(uint8_t* ar, int x, int y, int x2, int y2, Color8u c){
	int dx = (x2 - x);
	int dy = (y2 - y);
	float m = (1.0 * dy) / (1.0 * dx);
	int yv;
	int temp;
	if(m <= 1.0 && m >= -1.0){
		if(x > x2){
			temp = x;
			x = x2;
			x2 = temp;
		};
		for (int i = x; i < x2; i++){
			yv = m * i - m * x + y + 0.5;
			setPixel(ar, i, yv, c);
		};
	};
	if(!(m <= 1.0 && m >= -1.0)){
		if(y > y2){
			temp = y;
			y = y2;
			y2 = temp;
		};
		for (int i = y; i < y2; i++){
			yv = m * i - m * x + y + 0.5;
			yv = (i - .5 - y + m * x) / m;
			setPixel(ar, yv, i, c);
		};
	};
};

void MarkusHW01App::update()
{
	uint8_t* pixelArray = (*mySurface_).getData();

	drawRect(pixelArray, 0, 0, 640, 480, Color8u(0, 0, 0));

	drawCirc(pixelArray, 320, 240, 220, Color8u(255,0,0));

	drawLine(pixelArray, 400, 0, 320, 240, Color8u(0, 0, 255));

	/*if(color1 != 0.0){
	color1 = color1 - 0.015;
	};

	//if(color1 < 0.0){
	//	color1 = 1.0;
	//};

	if(color1 < 0.0 && color2 != 0.0){
	color2 = color2 - 0.015;
	};

	if(color1 < 0.0 && color2 < 0.0 && color3 != 0.0){
	color3 = color3 - 0.015;
	};
	
	if(color1 < 0.0 && color2 < 0.0 && color3 < 0.0){
	color1 = 1.0;
	color2 = 1.0;
	color3 = 1.0;
	//iteration = rand() % 6;
	iteration = iteration + 1;
	if(iteration == 6){
		iteration = 0;
	};
	};*/

};


void MarkusHW01App::draw()
{
	// clear out the window with black
	/*if(iteration == 0){
	gl::clear( Color( color1, color2, color3 ) ); 
	};

	if(iteration == 3){
	gl::clear( Color( color1, color3, color2 ) ); 
	};

	if(iteration == 1){
	gl::clear( Color( color2, color1, color3 ) ); 
	};

	if(iteration == 4){
	gl::clear( Color( color3, color1, color2 ) ); 
	};

	if(iteration == 2){
	gl::clear( Color( color2, color3, color1 ) ); 
	};

	if(iteration == 5){
	gl::clear( Color( color3, color2, color1 ) ); 
	};*/

	gl::draw(*mySurface_);
};

CINDER_APP_BASIC( MarkusHW01App, RendererGl )
