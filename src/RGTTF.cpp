#include "rgui/RGTTF.hpp"

//#include <ft2build.h>
//#include FT_FREETYPE_H



RGTTF::RGTTF(){
    fontValid = false;
}

void RGTTF::loadFont(string fontFile, int newFontSize) {
    fontValid = true;
    //initialize freetype library
	FT_Error ftError = FT_Init_FreeType( &ftLibrary );
	if(ftError) {
        cout << "RGTTF: A freetype error occurred during initialization" << endl;
        fontValid = false;
	}

	fontRenderSize = newFontSize;
    this->fontFile = fontFile;

    //build absolute path from current working directory
    string fontPath = "/"+fontFile;
    char currDir[1024];

    fontPath = getcwd(currDir, 1024) + fontPath;

    //load the font face
	ftError = FT_New_Face( ftLibrary, fontPath.c_str(), 0, &face);
	if(ftError) {
        cout << "RGTTF: An error occured while loading the font, CHECK YOUR FILENAME!" << endl;
        cout << "maybe the font isn't in the data directory? freetype is reporting this file: " << fontPath.c_str() << " is cannot be found." << endl;
        fontValid = false;
	}

    if(fontValid) {
        //setup character sizes
        FT_Set_Char_Size( face,
                         0, newFontSize << 6, //in 1/64th of a font point, <<6 == *64
                         72, 72);   //vertical and horizontal device resolution
        faceSize = newFontSize;

        slot = face->glyph;

        border = 3;
        visibleBorder = 2;

        singleLineH = newFontSize * 1.43;
    }
}

RGTTF::~RGTTF() {
    fontValid = false;
    //cleanup
    //FT_Done_Face(face);
	//FT_Done_FreeType(ftLibrary);

	//release gl textures... THIS MAY NOT ACTUALLY WORK (you've been warned)
	/*cout << "RGTTF: Freetype unloading. Attempting to release RGTTF gl textures... this might not go well" << endl;
    map<unsigned short ,map<wchar_t, GLuint> >::const_iterator end = charTextures.end();
    map<unsigned short ,map<wchar_t, GLuint> >::const_iterator it;
	for(it=charTextures.begin(); it!=end; ++it) {
	    map<wchar_t, GLuint>::const_iterator end2 = it->second.end();
        map<wchar_t, GLuint>::const_iterator it2;
        for(it2=charTextures[it->first].begin(); it2!=end2; ++it2) {
            glDeleteTextures(1, &it2->second);
        }
	}*/
}

/*!
Builds and stores an opengl texture for a character with a given size. Texture handles and character
properties are stored inside data structures in the RFTTF

Returns the handle to the opengl texture the character was drawn in.
*/
GLuint RGTTF::buildTextureForChar(unsigned short charSizePts, wchar_t c){
    FT_Error error;

    //switch the face size if nescessary for the FT_Face object
    if(faceSize != charSizePts) {
        FT_Set_Char_Size( face,
                         0, charSizePts << 6, //in 1/64th of a font point, <<6 == *64
                         72, 72);   //vertical and horiziontal device resolution
        faceSize = charSizePts;
    }

    charProperties[charSizePts][c] = charProperty();

    if(FT_Load_Char( face,  c, FT_LOAD_RENDER )){
        cout << "Error with FT_Load_Glyph" << endl;
    }

    int width  = nextPowerOf2( slot->bitmap.width + border*2 );
    int height = nextPowerOf2( slot->bitmap.rows + border*2 );

    charProperties[charSizePts][c].width = width;
    charProperties[charSizePts][c].height = height;
    charProperties[charSizePts][c].bitW = slot->bitmap.width;
    charProperties[charSizePts][c].bitH = slot->bitmap_top;
    charProperties[charSizePts][c].horiBearingX = slot->bitmap_left;
    charProperties[charSizePts][c].horiBearingY = slot->bitmap_top;
    charProperties[charSizePts][c].horiAdvance = slot->advance.x >> 6;

    //cout << "w: " << charProperties[c].width << "h: " <<charProperties[c].height << " horBearX: " << charProperties[c].horiBearingX
    //    << " horBearY: " << charProperties[c].horiBearingY << " bitW: " << charProperties[c].bitW<< " bitH: " << charProperties[c].bitH << " hAdv: " << charProperties[c].horiAdvance << " char: " << c << endl;

    //allocate space for texture data
    GLubyte* data = new GLubyte[ 2 * width * height];
    for(int i=0; i < 2*width*height; i+=2) {
        data[i] = 255;   //fully white
        data[i+1] = 0;   //fully transparent
    }

    for(int j=0; j < height; j++) {
        for(int i=0; i < width; i++){
            if(i<slot->bitmap.width && j<slot->bitmap.rows) {
                data[2*((i+border)+(j+border)*width)+1] = slot->bitmap.buffer[i + slot->bitmap.pitch*j];
            }
        }
    }
    charTextures[charSizePts][c] = 0;
    glGenTextures(1, &charTextures[charSizePts][c]);
    glBindTexture( GL_TEXTURE_2D, charTextures[charSizePts][c]);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
           0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data );

    delete [] data;

	return charTextures[charSizePts][c];
}


void RGTTF::drawString(wstring text, int x, int y, ColorRGBA textColor) {
    drawString(text, x, y, textColor, RG_LEFT_TEXT_LINE);
}

/*!
Justification is one of the following constants:
RG_LEFT_TEXT_LINE - The text is left justified by the baseline of the first line of text
Justification defines where the text is drawn from

Note: A wstring is specified like this: wstring bob = L"String with 漢字";

If you get an error "Converting to execution character set: Illegal byte sequence" please ensure the encoding of
your file is set to something that can handle the characters you've used, UTF8 is recommended for all files.
*/
void RGTTF::drawString(wstring text, int x, int y, ColorRGBA textColor, int justification) {
    if(fontValid){
        //setup position variables
        int cursorX=0, cursorY=0; //drawing positions

        glPushMatrix();
        glTranslatef(x,y,0);
        //itterate through each character in the text
        for(int i=0; i<text.length(); i++) {

            if(text.at(i) == '\n') {    //a line return?
                cursorY += singleLineH;
                cursorX = 0;
            } else {    //or a normal character?
                if(charTextures[fontRenderSize].count( text.at(i) ) == 0) {   //already rendered to a texture?
                    buildTextureForChar(fontRenderSize, text.at(i));
                    //cout << "texture built for: " << text.at(i) << endl;
                }
                charProperty property = charProperties[fontRenderSize][text.at(i)];



                //draw the character
                int x1 = property.horiBearingX + cursorX;
                int w1 = property.width;
                int y1;
                if(justification == RG_LEFT_TEXT_LINE) {    //initial justification fiddling
                    y1 = -property.horiBearingY + cursorY;
                } else {
                    y1 = -property.horiBearingY + cursorY;
                }

                int h1 = property.height;



                GLfloat verteces[] = {       GLfloat(x1),       GLfloat(y1),
                                             GLfloat(x1 + w1),  GLfloat(y1),
                                             GLfloat(x1 + w1),  GLfloat(y1 + h1),
                                             GLfloat(x1),       GLfloat(y1 + h1) };
                GLfloat texCoords[] = { 0, 0,
                                        1, 0,
                                        1, 1,
                                        0, 1 };
                glBindTexture(GL_TEXTURE_2D, charTextures[fontRenderSize][text.at(i)]);
                glNormal3f(0, 0, 1);

                glEnable(GL_TEXTURE_2D);
                glColor4ub(textColor.r(), textColor.g(), textColor.b(), textColor.a());
                glEnableClientState( GL_TEXTURE_COORD_ARRAY );
                glTexCoordPointer(2, GL_FLOAT, 0, texCoords );
                glEnableClientState( GL_VERTEX_ARRAY );
                glVertexPointer(2, GL_FLOAT, 0, verteces );
                glDrawArrays( GL_QUADS, 0, 4 );
                glDisableClientState( GL_TEXTURE_COORD_ARRAY );
                glDisable(GL_TEXTURE_2D);


                //advance the cursor
                cursorX += property.horiAdvance ;

            }

        }

        glPopMatrix();

    }

}


void RGTTF::setFontSize(unsigned short newSize){
    fontRenderSize = newSize;
}
unsigned short RGTTF::getFontSize(){
    return fontRenderSize;
}

bool RGTTF::isValid() {
    return fontValid;
}


/*!
Box dimensions are returned relative to the place where the text is drawn from (it's justification)

See RGRect for more details on the returned structure

Note: when using japanese characters sometimes the bounding box will be a little bit undersized. This probable extends to
other non-latin characters as well. There could be some sort of problem with only using the horizontal advance to calculate
the width. Right now I'm adding 1 to compensate, but it's not perfect.
*/
RGBB RGTTF::boundingBox(wstring text){
    RGBB result;
    result.x = 0;
    result.y = 0;
    result.width = 0;
    result.height = 0;

    if(fontValid){
        //setup position variables
        int cursorX=0, cursorY=0; //drawing positions

        int boxW=-1;
        int boxH=-1;
        int xOffset=-1, yOffset=-1;

        vector<int> lineWidth;
        int currentLine=0;
        lineWidth.push_back(0);

        vector<int> lineMaxYBearing;
        lineMaxYBearing.push_back(0);

        for(int i=0; i<text.length(); i++) {
            if(text.at(i) == '\n') {    //a line return?
                cursorY += singleLineH;     //advance the Y cursor
                currentLine += 1;           //increment the current line counter
                cursorX = 0;                //reset the X cursor since it;s a new line
                lineWidth.push_back(0);        //insert a new line width variable for this line
                lineMaxYBearing.push_back(0);        //insert a new max line bearing variable for this line
            } else {                    //or a normal character?
                if(charTextures[fontRenderSize].count( text.at(i) ) == 0) {   //already rendered to a texture? (cacheing)
                    buildTextureForChar(fontRenderSize, text.at(i));
                }
                charProperty property = charProperties[fontRenderSize][text.at(i)];

                lineWidth.at(currentLine) += property.horiAdvance + 1;

                if(property.horiBearingY > lineMaxYBearing.at(currentLine)) {
                    lineMaxYBearing.at(currentLine) = property.horiBearingY;
                }
            }

        }

        //find maximum dimensions
        for(int i=0; i<lineWidth.size(); i++){
            if(lineWidth.at(i) > boxW) {
                boxW = lineWidth.at(i);
            }
        }
        boxH = (currentLine+1)*singleLineH; //calculate bounding box height from the number of total lines

        result.x = 0;
        result.y = -1*lineMaxYBearing.at(0);
        result.width = boxW;
        result.height = boxH;
        return result;
    } else {
        return result;
    }
}

pair <int,int> RGTTF::boundingDims(wstring text) {
    RGBB bb = boundingBox(text);

    if(fontValid){
        pair <int,int> result ( bb.width, bb.height);
        return result;
    } else {
        return pair<int,int>(0,0);
    }
}


/*!
Useful for sizing textures and such, belongs in utilities or basic math eventually
*/
int nextPowerOf2(int input){
    int value = 1;
    while(value<input){
        value <<= 1;
    }
    return value;
}
