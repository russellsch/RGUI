#include "RGDrawInterface.h"

RGDrawInterface::RGDrawInterface(RGDrawImplementation* newImp){
	implementation = newImp;
}

void RGDrawInterface::noStroke(){ implementation->noStroke(); }

void RGDrawInterface::stroke(int brightness){ 
	implementation->stroke( brightness, brightness, brightness, 255 ); 
}
void RGDrawInterface::stroke(int brightness, int alpha){ 
	implementation->stroke( brightness, brightness, brightness, alpha); 
}
void RGDrawInterface::stroke(int r, int g, int b){ 
	implementation->stroke( r, g, b, 255); 
}
void RGDrawInterface::stroke(int r, int g, int b, int a){ 
	implementation->stroke( r, g, b, a); 
}

void RGDrawInterface::noFill(){ implementation->noFill(); }
void RGDrawInterface::fill(int brightness){ implementation->fill( brightness, brightness, brightness, 255); }
void RGDrawInterface::fill(int brightness, int alpha){ implementation->fill( brightness, brightness, brightness, alpha); }
void RGDrawInterface::fill(int r, int g, int b){ implementation->fill( r, g, b, 255); }
void RGDrawInterface::fill(int r, int g, int b, int a){ implementation->fill( r, g, b, a); }

/*void RGDrawInterface::line(int x1, int y1, int x2, int y2){ implementation->line( x1, y1, x2, y2); }
void RGDrawInterface::rect(int x1, int y1, int w, int h){ implementation->rect( x1, y1, w, h); }
void RGDrawInterface::circle(float x1, float y1, float radius){ implementation->circle( x1, y1, radius); }
void RGDrawInterface::circle(float x1, float y1, float radius, int res){ implementation->circle( x1, y1, radius, res); }*/

void RGDrawInterface::pushMatrix(){ implementation->pushMatrix(); }
void RGDrawInterface::popMatrix(){ implementation->popMatrix(); }

void RGDrawInterface::translate(int x, int y){ implementation->translate( (float)x, (float)y); }
void RGDrawInterface::translate(float x, float y){ implementation->translate( x,  y); }
//void RGDrawInterface::translate(int x, int y, int z){ implementation->translate( (float)x, (float)y, (float)z); }
//void RGDrawInterface::translate(float x, float y, float z){ implementation->translate( x,  y,  z); }