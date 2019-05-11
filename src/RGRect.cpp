#include "rgui/RGRect.hpp"

RGRect::RGRect(float x, float y, float width, float height, int positionMode) {
    this->width = width;
    this->height = height;
    this->positionMode = positionMode;

    if(positionMode == RG_TC) {
        left = x - (width/2);
        top = y;
    }
    else if(positionMode == RG_TR) {
        left = x - width;
        top = y;
    }
    else if(positionMode == RG_CL) {
        left = x;
        top = y - (height/2);
    }
    else if(positionMode == RG_CC) {
        left = x - (width/2);
        top = y - (height/2);
    }
    else if(positionMode == RG_CR) {
        left = x - width;
        top = y - (height/2);
    }
    else if(positionMode == RG_BL) {
        left = x;
        top = y - height;
    }
    else if(positionMode == RG_BC) {
        left = x - (width/2);
        top = y - height;
    }
    else if(positionMode == RG_BR) {
        left = x - width;
        top = y - height;
    } else {    //RG_TL
        left = x;
        top = y;
    }
    //std::cout << "Rect here w:" << width << std::endl;
    transMatrix.data[0][0] =  1;
	transMatrix.data[0][1] =  0;
	transMatrix.data[0][2] =  0;
	transMatrix.data[0][3] =  0;
	transMatrix.data[1][0] =  0;
	transMatrix.data[1][1] =  1;
	transMatrix.data[1][2] =  0;
	transMatrix.data[1][3] =  0;
	transMatrix.data[2][0] =  0;
	transMatrix.data[2][1] =  0;
	transMatrix.data[2][2] =  1;
	transMatrix.data[2][3] =  0;
	transMatrix.data[3][0] =  left;
	transMatrix.data[3][1] =  top;
	transMatrix.data[3][2] =  0;
	transMatrix.data[3][3] =  1;

    //transMatrix.print();
}


void RGRect::translate(float x, float y) {
    left += x;
    top += y;
    transMatrix.data[3][0] = left;
    transMatrix.data[3][1] = top;
}

/*!
Returns a 4x4 matrix. This matrix can be used to to draw a point on the rectangle, referring to the top left corner as the origin.
So if you wanted to draw a point at the the top left corner, you would multiple your point by this matrix to determine where to draw.
This takes care of rotation and translation, and allows you to draw on the object as if it was your canvas.
*/
TransformMatrix3 RGRect::getTransformMatrix() {
    return transMatrix;
}

/*!
Returns a rectangle that is the intersection of two rectangles
Assumes both rectangles are relative to the same origin (hopefully that's obvious).
*/
RGRect RGRect::getIntersection(RGRect* r2){
    RGRect result(0,0,0,0, RG_TL);
    if(intersect(r2)) {
        result.setL( MAX(getTLX(), r2->getTLX()) );
        result.setT( MAX(getTLY(), r2->getTLY()) );

        result.setW( ( (getTLX()< r2->getTLX()) ?  abs(getTRX() - r2->getTLX()) : abs(r2->getTRX() - getTLX()) ) );
        result.setH( ( (getTLY()< r2->getTLY()) ?  abs(getTRY() - r2->getTLY()) : abs(r2->getTRY() - getTLY()) ) );
    } else {
		//std::cout << "NO INTERSECTION"<< std:: endl;
	}
	return result;
}


bool RGRect::intersect(RGRect* r2) {
    return !(   r2->getTLX() >= getTRX() ||
                r2->getTRX() <= getTLX() ||
                r2->getTLY() >= getBRY() ||
                r2->getBRY() <= getTLY()      );
}


bool RGRect::intersect(float x, float y){
	return (	x >= getLeft() &&
				x <= getRight() && 
				y >= getTop() && 
				y <= getBottom()		);
}

void RGRect::setPositionMode(int positionModeNew) {
    positionMode = positionModeNew;
}

/*!
Adjusts the left value of the rectangle depending on the positionMode. Essentiall the rectangle is
resized around the point defined in position mode
*/
void RGRect::setW(float wNew) {
    if(positionMode == RG_TL || positionMode == RG_CL || positionMode == RG_BL) {
        //width = wNew;
    } else if(positionMode == RG_TC || positionMode == RG_CC || positionMode == RG_BC) {
        left -= (wNew-width)/2;
        transMatrix.data[3][0] = left;
        //width = wNew;
    } else if(positionMode == RG_TR || positionMode == RG_CR || positionMode == RG_BR) {
        left += width - wNew;
        transMatrix.data[3][0] = left;
        //width = wNew;
    }
    width = wNew;
}
/*!
Adjusts the left value of the rectangle depending on the positionMode. Essentially the rectangle is
resized around the point defined in position mode
*/
void RGRect::setWidth(float wNew) {
    RGRect::setW(wNew);
}


/*!
Adjusts the top value of the rectangle depending on the positionMode. Essentially the rectangle is
resized around the point defined in position mode
*/
void RGRect::setH(float hNew) {
    if(positionMode == RG_TL || positionMode == RG_TC || positionMode == RG_TR) {
        //height = hNew;
    } else if(positionMode == RG_CL || positionMode == RG_CC || positionMode == RG_CR) {
        top -= (hNew-height)/2;
        transMatrix.data[3][1] = top;
        //height = hNew;
    } else if(positionMode == RG_BL || positionMode == RG_BC || positionMode == RG_BR) {
        top += height - hNew;
        transMatrix.data[3][1] = top;
        //height = hNew;
    }
    height = hNew;
}
/*!
Adjusts the top value of the rectangle depending on the positionMode. Essentially the rectangle is
resized around the point defined in position mode
*/
void RGRect::setHeight(float hNew) {
    RGRect::setH(hNew);
}


void RGRect::setX(float xNew) {
    if(positionMode == RG_TL || positionMode == RG_CL || positionMode == RG_BL) {
        left = xNew;
    } else if(positionMode == RG_TC || positionMode == RG_CC || positionMode == RG_BC) {
        left = xNew - (width/2);
    } else if(positionMode == RG_TR || positionMode == RG_CR || positionMode == RG_BR) {
        left = xNew - width;
    }
}
void RGRect::setY(float yNew){
    if(positionMode == RG_TL || positionMode == RG_TC || positionMode == RG_TR) {
        top = yNew;
    } else if(positionMode == RG_CL || positionMode == RG_CC || positionMode == RG_CR) {
        top = yNew - (height/2);
    } else if(positionMode == RG_BL || positionMode == RG_BC || positionMode == RG_BR) {
        top = yNew - height;
    }
}


void RGRect::setL(float lNew) {
    left = lNew;
    transMatrix.data[3][0] = left;
}
void RGRect::setLeft(float lNew) {
    left = lNew;
    transMatrix.data[3][0] = left;
}
void RGRect::setT(float tNew) {
    top = tNew;
    transMatrix.data[3][1] = top;
}
void RGRect::setTop(float tNew) {
    top = tNew;
    transMatrix.data[3][1] = top;
}




/*float RGRect::getL() const {
    return left;
}*/
/*float RGRect::getLeft() const {
    return left;
}*/
float RGRect::getR() const {
    return left+width;
}
float RGRect::getRight() const {
    return left+width;
}
float RGRect::getT() const {
    return top;
}
float RGRect::getTop() const {
    return top;
}
float RGRect::getB() const {
    return top+height;
}
float RGRect::getBottom() const {
    return top+height;
}

float RGRect::getW() const {
    return width;
}
float RGRect::getWidth() const {
    return width;
}
float RGRect::getH() const {
    return height;
}
float RGRect::getHeight() const {
    return height;
}

//functions for getting various useful points around the RGObject
//   ____________
//  |TL  TC  TR |
//  |CL  CC  CR |
//  |BL  BC  BR |
//   ------------

/*!
Gets the x position of the current location of the positionMode point
*/
float RGRect::getX() const{
    if(positionMode == RG_TL || positionMode == RG_CL || positionMode == RG_BL) {
        return left;
    } else if(positionMode == RG_TC || positionMode == RG_CC || positionMode == RG_BC) {
		return left + (width/2);
    } else if(positionMode == RG_TR || positionMode == RG_CR || positionMode == RG_BR) {
        return left + width;
    }
	return 0; //shouldn't happen
}
/*!
Gets the y position of the current location of the positionMode point
*/
float RGRect::getY() const{
    return top;
    if(positionMode == RG_TL || positionMode == RG_TC || positionMode == RG_TR) {
        return top;
    } else if(positionMode == RG_CL || positionMode == RG_CC || positionMode == RG_CR) {
        return top + (height/2);
    } else if(positionMode == RG_BL || positionMode == RG_BC || positionMode == RG_BR) {
        return top + height;
    }
	return 0; //shouldn't happen
}

float RGRect::getTLX() const {
    return left;
}
float RGRect::getTLY() const{
    return top;
}
float RGRect::getTCX() const{
    return left + (width/2);
}
float RGRect::getTCY() const{
    return top;
}
float RGRect::getTRX() const{
    return left + width;
}
float RGRect::getTRY() const{
    return top;
}
float RGRect::getCLX() const{
    return left;
}
float RGRect::getCLY() const{
    return top + (height/2);
}
float RGRect::getCenterX() const{
    return getCCX();
}
float RGRect::getCenterY() const{
    return getCCY();
}

float RGRect::getCCX() const{
    return left + (width/2);
}
float RGRect::getCCY() const{
    return top + (height/2);
}
float RGRect::getCRX() const{
    return left + width;
}
float RGRect::getCRY() const{
    return top + (height/2);
}
float RGRect::getBLX() const{
    return left;
}
float RGRect::getBLY() const{
    return top + height;
}
float RGRect::getBCX() const{
    return left + (width/2);
}
float RGRect::getBCY() const{
    return top + height;
}
float RGRect::getBRX() const{
    return left + width;
}
float RGRect::getBRY() const{
    return top + height;
}


std::ostream& operator<< ( std::ostream& o,  const RGRect& rect )
{
	return o << "TL:(" << rect.getTLX() << ", " << rect.getTLY() << ") w,h:(" << rect.getW() << ", " << rect.getH() << ")";
}
