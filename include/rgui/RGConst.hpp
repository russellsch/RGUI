#ifndef RGCONST_H
#define RGCONST_H


//Determine System Type
#if defined( __WIN32__ ) || defined( _WIN32 )
	#define TARGET_WIN32
    #if (_MSC_VER)  //If we:re in visual studio setup a special define
        #define TARGET_WIN32_VC
    #endif

#elif defined( __APPLE_CC__)
	#include <TargetConditionals.h>

	#if (TARGET_OF_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE)
		#define TARGET_OF_IPHONE
		#define TARGET_OPENGLES
	#else
		#define TARGET_OSX
	#endif
#else
	#define TARGET_LINUX
#endif





//EVENT DEFINITIONS
#define RG_PRESS 0x01
#define PRESSED 0x01
#define RG_RELEASE 0x02
#define RELEASED 0x02
#define DRAGGED 0x03
#define RG_DRAGGED 0x03


//Defines the points of a rectangle
        //  |TL  TC  TR |
        //  |CL  CC  CR |
        //  |BL  BC  BR |
        //   ------------
#define CORNER 0x01
#define CENTER 0x05
#define RG_TL 0x01
#define RG_TOPLEFT 0x01
#define RG_TC 0x02
#define RG_TOPCENTER 0x02
#define RG_TR 0x03
#define RG_TOPRIGHT 0x03
#define RG_CL 0x04
#define RG_CENTERLEFT 0x04
#define RG_CC 0x05
#define RG_CENTERCENTER 0x05
#define RG_CR 0x06
#define RG_CENTERRIGHT 0x06
#define RG_BL 0x07
#define RG_BOTTOMLEFT 0x07
#define RG_BC 0x08
#define RG_BOTTOMCENTER 0x08
#define RG_BR 0x09
#define RG_BOTTOMRIGHT 0x09

//Additionally for text, the following constants are defined
#define RG_LEFT_TEXT_LINE 0x51




//Orientation
enum class RGOrientation {
    VERTICAL,
    HORIZONTAL,
};

#define RG_MAX_CIRCLE_PTS 300


#define RG_FLOAT 0x01
#define RG_INT 0x02

#ifndef PI
    #define PI 3.14159
#endif


#ifndef MIN
	#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
	#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef CLAMP
	#define CLAMP(value, min, max) ( MAX( MIN(value, max), min) )
#endif


//THIS PROBABLY BELONGS IN SOME SORT OF "TYPES" FILE
//!Rectangle structure for holding properties of a rectangle
/*!
* x is x position
* y is y position
* width is rectangle width
* height is rectangle height
*/
typedef struct {
    int x;
    int y;
    int width;
    int height;

} RGBB;

//!Point structure for holding properties of a 2D point
/*!
x and y are the point's x and y position
*/
typedef struct {
    int x;
    int y;
} RGPoint2D;


enum class MouseButton {
    Left,
    Right,
    Middle,
    Button4,
    Button5,
    ButtonCount
};




enum class MouseDelegation {
    NOT_ACCEPTED,     // Mouse event not accepted by this or any child
    THIS_ACCEPTED,    // Mouse event accepted by this object
    CHILD_ACCEPTED,   // Mouse event accepted by a child (or sub-child) of this object
    BLOCKING,         // Mouse event not accepted, but should not be propagated to children
};




#endif // RGCONST_H









