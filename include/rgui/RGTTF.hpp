#ifndef RGTTF_H
#define RGTTF_H


#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GL/glew.h"
#include "unistd.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "RGConst.hpp"
#include "ColorRGBA.hpp"


/*(//foward declarations so we don't need to reference freetype headers in the headers
using FT_Library = FT_LibraryRec_*;
using FT_Face = struct FT_FaceRec_*;
using FT_GlyphSlot = struct FT_GlyphSlotRec_*;*/




//!Struct defining useful properties stored for each rendered TTF character
/*!
See freetype website for more information on these parameters (http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html)
*/
typedef struct {
    int width;  //!<Width of the gltexture
    int height; //!<Height of the gltexture
    int bitW;   //!<Width of the glyph bitmap in pixels
    int bitH;   //!<Height of the glyph bitmap in pixels
    int horiBearingX;   //!<Distance from bitmap leftmost pixel to y-axis (left border)
    int horiBearingY;   //!<Distance from bitmap topmost pixel to x-axis (how far above line)
    int horiAdvance;    //!<How far to advance the pen when drawing horizontally
} charProperty;


//!Class for rendering TTF fonts
/*!
Each instance is meant to contain one font with multiple sizes.

This class is not meant for general use and requires an existing opengl context.
Text rendering in programs using the RGUI should be done through the text function of an RGDraw object.

This class renders characters to opengl texture buffers which are then cached.
*/
class RGTTF {
    public:
        RGTTF();
        void loadFont(std::string fontFile, int newFontSize);   //!<Constructor loads and sets up a given font at a given size
        virtual ~RGTTF();

        void drawString(std::wstring text, int x, int y, ColorRGBA textColor);    //!<Basic string drawing function, uses default justification
        void drawString(std::wstring text, int x, int y, ColorRGBA textColor, int justification); //!<Basic string drawing function, with custom justification

        void setFontSize(unsigned short newSize);
        unsigned short getFontSize();

        bool isValid();

        RGBB boundingBox(std::wstring text); //!<Returns dimensions of a box that will enclose rendered text
        std::pair <int,int> boundingDims(std::wstring text);  //!<Returns width and height of a string when rendered




    protected:
        GLuint buildTextureForChar(unsigned short charSizePts, wchar_t c);      //!<Builds an opengl character texture for later use
        bool fontValid;
    private:
        FT_Library ftLibrary;   //!<Freetype font library handle
        FT_Face face;   //!<Freetype font face handle
        unsigned short faceSize;    //!<Current internal size of the FT_Face object

        FT_GlyphSlot slot;

        int singleLineH;    //!<height of a single line of text

        std::string fontFile;    //!<filename of font being used
        int fontRenderSize;       //!<all strings drawn will be in this size

        int border;
		int visibleBorder;


        std::map<unsigned short, std::map<wchar_t, GLuint> > charTextures;              //!<Associates a given character to a gl texture
        std::map<unsigned short, std::map<wchar_t, charProperty> > charProperties;      //!<Associates a given character to a list of properties for the glyph and the gl texture
};

//!Find the next power of 2 larger than the input number
int nextPowerOf2(int input);

#endif // RGTTF_H
