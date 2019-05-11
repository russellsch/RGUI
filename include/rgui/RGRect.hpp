#ifndef RGRECT_H
#define RGRECT_H

#include <rgui/RGConst.hpp>
#include <iostream>
#include <cmath>

//!4x4 transformation matrix for use with openGL
struct TransformMatrix3 {
    float data[4][4];
    void print() {
        for(int i=0; i < 4; i++) {
            for(int j=0; j < 4; j++) {
                std::cout << data[i][j] << "\t";
            }
             std::cout << std::endl;
        }
    }
};

using namespace std;

//!Represents a manipulatable rectangle in 2D space
/*!
A rectangle has something called a positionMode. This initially determines how you are placing the rectangle (common
values are the top left corner, and the center). You can query the rectangle for the X and Y positions of various
points around the rectangle.

The possible position mode positions are:

<TABLE>
    <TR><TD>RG_TL</TD>  <TD>RG_TC</TD>  <TD>RG_TR</TD></TR>
    <TR><TD>RG_CL</TD>  <TD>RG_CC</TD>  <TD>RG_CR</TD></TR>
    <TR><TD>RG_BL</TD>  <TD>RG_BC</TD>  <TD>RG_BR</TD></TR>
</TABLE>

This mode position can be changed after the fact. This can be useful for resizing from a reference point, or for things
like modifying alignment. Figure out something nifty.

Definitions: t refers to top, b to bottom, l to left, r to right, and c to center, x and y refer to coordinates based on
the positionMode position on the rectangle, w and h refer to width and height.

l and t very specifically refer to the top and left values of the rectangle (distance to top left corner). Even if the
rectangle were to be rotated, l and t would still refer to the corner that was top left before the rotation.

Internally the rectangle's size and position are stored only by top, left, width and heigt. All other values
are calculated on the fly as needed.


TODO:
* Add rotation. Thought needs to be given on how to non-destructively apply rotation to the translation matrix, while still allowing resizing...
perhaps switch to using scaling the in the matrix to represent width and height?
* Mouse collision checking? Apply transform to mouse point and see if it is > 0 and < width and height
* Add resizing, with an anchor point, specifying anchor and stretch parameters

*/


class RGRect
{
    public:

        RGRect(float x, float y, float widthNew, float heightNew, int positionModeNew); //!< Rectangle constructor

        void translate(float x, float y);   //!<Translates the position rectangle in 2D space
        // TODO: void rotateDeg(float degrees);
        // TODO: void rotateRad(float degrees);
        TransformMatrix3 getTransformMatrix();           //!<Returns the transform matrix for the translation and rotation of this rectangle (currently non-functional)

        RGRect getIntersection(RGRect* r2);         //!<Returns a rectangle of the intersection of this rectangle and another
        bool intersect(RGRect* r2);                 //!<Returns true if this rectangle interesects with another
		bool intersect(float x, float y);           //!<Returns true if a point intersectes the rectangle

        void setPositionMode(int positionModeNew);
		int getPositionMode() {return positionMode; };

        void setW(float wNew);      //!<Set the width of the rectangle
        void setWidth(float wNew);  //!<Set the width of the rectangle
        void setH(float hNew);      //!<Set the height of the rectangle
        void setHeight(float hNew); //!<Set the height of the rectangle

        void setL(float lNew);      //!< Sets the distance from the origin to the left of the rectangle
        void setLeft(float lNew);   //!< Sets the distance from the origin to the left of the rectangle
        void setT(float tNew);      //!< Sets the distance from the origin to the top of the rectangle
        void setTop(float tNew);    //!< Sets the distance from the origin to the top of the rectangle

        void setX(float xNew);      //!<Set the X position of whatever point the position mode is set to
        void setY(float yNew);      //!<Set the Y position of whatever point the position mode is set to



        float getLeft() const {return left;}        //!<Get the distance from the origin to the left of the rectangle
        float getL() const {return getLeft();};           //!<Get the distance from the origin to the left of the rectangle
        float getRight() const;       //!<Get the distance from the origin to the right of the rectangle
        float getR() const;           //!<Get the distance from the origin to the right of the rectangle
        float getT() const;           //!<Get the distance from the origin to the top of the rectangle
        float getTop() const;         //!<Get the distance from the origin to the top of the rectangle
        float getB() const;           //!<Get the distance from the origin to the bottom of the rectangle
        float getBottom() const;      //!<Get the distance from the origin to the bottom of the rectangle

        float getW() const;           //!<Get the width of the rectangle
        float getWidth() const;       //!<Get the width of the rectangle
        float getH() const;           //!<Get the height of the rectangle
        float getHeight() const;      //!<Get the height of the rectangle

        //functions for getting various useful points around the RGObject
        //these are relative to the position mode point
        //   ____________
        //  |TL  TC  TR |
        //  |CL  CC  CR |
        //  |BL  BC  BR |
        //   ------------
        float getX() const;     //!<Get the X position of wherever the position mode is set to
        float getY() const;     //!<Get the Y position of wherever the position mode is set to

        float getTLX() const;   //!<Get top left X coordinate
        float getTLY() const;   //!<Get top left Y coordinate
        float getTCX() const;   //!<Get top center X coordinate
        float getTCY() const;   //!<Get top center Y coordinate
        float getTRX() const;   //!<Get top right X coordinate
        float getTRY() const;   //!<Get top right Y coordinate
        float getCLX() const;   //!<Get left center X coordinate
        float getCLY() const;   //!<Get left center Y coordinate
        float getCenterX() const; //!<Get center X coordinate
        float getCenterY() const; //!<Get center Y coordinate
        float getCCX() const;   //!<Get center X coordinate
        float getCCY() const;   //!<Get center Y coordinate
        float getCRX() const;   //!<Get right center X coordinate
        float getCRY() const;   //!<Get right center Y coordinate
        float getBLX() const;   //!<Get bottom left X coordinate
        float getBLY() const;   //!<Get bottom left Y coordinate
        float getBCX() const;   //!<Get bottom center X coordinate
        float getBCY() const;   //!<Get bottom center Y coordinate
        float getBRX() const;   //!<Get bottom right X coordinate
        float getBRY() const;   //!<Get bottom right Y coordinate

        friend std::ostream& operator<< ( std::ostream& o , const RGRect& rect);


    protected:

    private:
        float left;             //!<The distance from the left of the screen to the left of the rectangle
        float top;              //!<The distance from the top of the screen to the top of the rectangle
        float width;            //!<The width of the rectangle
        float height;           //!<The height of the rectangle
        int positionMode;
        TransformMatrix3 transMatrix;
};



#endif // RGRECT_H
