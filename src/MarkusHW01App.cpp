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
	void drawTri(uint8_t* ar, int x, int y, int x2, int y2, int x3, int y3, Color8u c);
	void blur(uint8_t* ar, float a,  float b,  float c,  float d,  float e,  float f,  float g,  float h,  float i);

  private:
	float color1;
	float color2;
	float color3;
	int iteration;
	Surface* mySurface_;
	uint8_t* pixelArray;
	int width;
	float a;
	int blured;
	int trix1;
	int trix2;
	int trix3;
	int triy1;
	int triy2;
	int triy3;
	int time;
	int circx;
	int circy;
	int col1;
	int col2;
	int col3;
};


void MarkusHW01App::setup()
{
	color1 = 1.0;
	color2 = 1.0;
	color3 = 1.0;
	iteration = 0;
	width = 640;
	blured = 0;
	trix1 = 0;
	trix2 = 0;
	trix3 = 0;
	triy1 = 0;
	triy2 = 0;
	triy3 = 0;
	time = 0;
	circx = 0;
	circy = 0;
	col1 = 0;
	col2 = 0;
	col3 = 0;

	mySurface_ = new Surface(1024,1024,false);
};

void MarkusHW01App::mouseDown( MouseEvent event )
{
	
	if(blured == 0){
		blured = 1;
	}
	else{
		blured = 0;
	};
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
			temp = y;
			y = y2;
			y2 = temp;
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
			temp = x;
			x = x2;
			x2 = temp;
		};
		for (int i = y; i < y2; i++){
			yv = m * i - m * x + y + 0.5;
			yv = (i - .5 - y + m * x) / m;
			setPixel(ar, yv, i, c);
		};
	};
};

void MarkusHW01App::drawTri(uint8_t* ar, int x, int y, int x2, int y2, int x3, int y3, Color8u c){
	drawLine(ar, x, y, x2, y2, c);
	drawLine(ar, x, y, x3, y3, c);
	drawLine(ar, x3, y3, x2, y2, c);
	
};

void MarkusHW01App::blur(uint8_t* ar , float a,  float b,  float c,  float d,  float e,  float f,  float g,  float h,  float i){

	float kernel [9] = {a,b,c,d,e,f,g,h,i};
	for(int i = 0; i < 640; i++){
		for(int j = 0; j < 480; j++){
			ar[j * 1024 * 3 + 3 * i] = ar[(j - 1) * 1024 * 3 + 3 * (i - 1)] * kernel[0] + ar[(j - 1) * 1024 * 3 + 3 * (i)] * kernel[1] + ar[(j - 1) * 1024 * 3 + 3 * (i + 1)] * kernel[2] + ar[(j) * 1024 * 3 + 3 * (i - 1)] * kernel[3] + ar[(j) * 1024 * 3 + 3 * (i)] * kernel[4] + ar[(j) * 1024 * 3 + 3 * (i + 1)] * kernel[5] + ar[(j + 1) * 1024 * 3 + 3 * (i - 1)] * kernel[6] + ar[(j + 1) * 1024 * 3 + 3 * (i)] * kernel[7] + ar[(j + 1) * 1024 * 3 + 3 * (i + 1)] * kernel[8];
			ar[j * 1024 * 3 + 3 * i + 1] = ar[(j - 1) * 1024 * 3 + 3 * (i - 1) + 1] * kernel[0] + ar[(j - 1) * 1024 * 3 + 3 * (i) + 1] * kernel[1] + ar[(j - 1) * 1024 * 3 + 3 * (i + 1) + 1] * kernel[2] + ar[(j) * 1024 * 3 + 3 * (i - 1) + 1] * kernel[3] + ar[(j) * 1024 * 3 + 3 * (i) + 1] * kernel[4] + ar[(j) * 1024 * 3 + 3 * (i + 1) + 1] * kernel[5] + ar[(j + 1) * 1024 * 3 + 3 * (i - 1) + 1] * kernel[6] + ar[(j + 1) * 1024 * 3 + 3 * (i) + 1] * kernel[7] + ar[(j + 1) * 1024 * 3 + 3 * (i + 1) + 1] * kernel[8];
			ar[j * 1024 * 3 + 3 * i + 2] = ar[(j - 1) * 1024 * 3 + 3 * (i - 1) + 2] * kernel[0] + ar[(j - 1) * 1024 * 3 + 3 * (i) + 2] * kernel[1] + ar[(j - 1) * 1024 * 3 + 3 * (i + 1) + 2] * kernel[2] + ar[(j) * 1024 * 3 + 3 * (i - 1) + 2] * kernel[3] + ar[(j) * 1024 * 3 + 3 * (i) + 2] * kernel[4] + ar[(j) * 1024 * 3 + 3 * (i + 1) + 2] * kernel[5] + ar[(j + 1) * 1024 * 3 + 3 * (i - 1) + 2] * kernel[6] + ar[(j + 1) * 1024 * 3 + 3 * (i) + 2] * kernel[7] + ar[(j + 1) * 1024 * 3 + 3 * (i + 1) + 2] * kernel[8];
		};
	};
};

void MarkusHW01App::update()
{
	uint8_t* pixelArray = (*mySurface_).getData();

	time++;

	

	if(blured == 0 && time % 3 == 0){
		console() << (rand() % 9) << endl;
		trix1 = trix1 + (rand() % 5 - 2);
		trix2 = trix2 + (rand() % 5 - 2);
		trix3 = trix3 + (rand() % 5 - 2);
		triy1 = triy1 + (rand() % 5 - 2);
		triy2 = triy2 + (rand() % 5 - 2);
		triy3 = triy3 + (rand() % 5 - 2);
		circx = circx + (rand() % 5 - 2);
		circy = circy + (rand() % 5 - 2);
		col1 = col1 + (rand() % 41 - 20);
		col2 = col2 + (rand() % 41 - 20);
		col3 = col3 + (rand() % 41 - 20);
	};

	drawRect(pixelArray, 0, 0, 640, 480, Color8u(125 + col1, 125 + col2, 125 + col3));

	drawRect(pixelArray, 300 + circx, 300 + triy2, 100 + triy1, 100 + trix1, Color8u(255, 0, 0));

	drawCirc(pixelArray, 320 + circx, 240 + circy, 120, Color8u(255,0,0));

	drawLine(pixelArray, 400 + trix3, 200 + trix1, 230 + triy2, 240 + triy3, Color8u(0, 0, 255));

	drawTri(pixelArray, 30 + trix1, 300 + triy1, 500 + trix2, 40 + triy2, 420 + trix3, 355 + triy3, Color8u(200, 0, 100));

	if(blured == 1)
	blur(pixelArray, 1/9.0,  1/9.0,  1/9.0,  1/9.0, 1/9.0,  1/9.0,  1/9.0,  1/9.0,  1/9.0);

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
