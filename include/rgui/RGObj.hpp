#ifndef RGOBJ_H
#define RGOBJ_H


#include <vector>
#include <string>


using namespace std;



#include "rgui/RGEventHandlerBase.hpp"
#include "rgui/RGDraw.hpp"
#include "rgui/RGRect.hpp"
#include "rgui/ColorRGBA.hpp"



class RGApp;


//!Base GUI object
/*!
All GUI object inherit from this base object. It is supposed to be as flexible, lightweight, and reusable as possible.

Adds the following primary functions to a rectangle:
- Hierarchy functionality: Represents the objects in a tree structure, with an RGRoot object at the top of the tree
- Interactivity: Mouse and keyboard functionality
- Hierarchical clipping functionality: as children are drawn clipping rectangles are passed down the tree

This object is meant to be subclassed to create new GUI controls. It is designed in such a way to provide interfaces
for both the people who make new controls and those to use new controls to attatch code. By overriding drag, press,
and release, a gui programmer can customize the functionality of the object. By attatching an event (using setEventHandler() ), and overriding
the event class's methods (see RGEvent), a user can easily link code to objects.

*/


class RGObj : public RGRect {
    public:

        RGDraw* draw = nullptr;           //!<pointer to the drawing instance
        bool drawValid;         //!<is the pointer to the drawing instance object valid



        bool clipChildren = false;      //!<Use glScissor to clip children outside this object's boundaries



        //standard color variables
        ColorRGBA bkgColor;           //!<background color
        ColorRGBA textColor;          //!<text color
        ColorRGBA borderColor;        //!<border color
        ColorRGBA foreColor;          //!<default color for filled objects above the background
        ColorRGBA activeColor;        //!<default color for active elements

        unsigned short fontSize;   //!<Default font size

        //DRAGGING VARIABLES
        RGObj* dragStart = nullptr;
        bool dragStartValid;
        int dragStartX, dragStartY;
        bool initialDrag;
        bool dragging;

        //Verbosity settings for debug
        bool verboseRender, verboseMouseOverChild, verbosePress, verboseRelease;




        //!Specifies if this object's position or size will change when parent is resized
        bool resizable;
        float anchorX, anchorY;
        float stretchX, stretchY;
        float leftOverStretchX;


        RGObj(const std::string& name, const std::string& type, int xNew, int yNew, int wNew, int hNew);
        ~RGObj() = default;

        //mouse clicking and dragging related
        MouseDelegation pressEvent(int mouseXin, int mouseYin);
        void releaseEvent(int mouseXin, int mouseYin);
        MouseDelegation dragEvent(int mouseXin, int mouseYin, int button);
        void resizeEvent(int wNew, int hNew);

        bool mouseOverChild(int mouseX, int mouseY, uint32_t childIndex);
        RGObj* getChild(int i);
        void addChild(RGObj* newChild); //!<Add a child to this GUI object
        int getChildrenSize() const;

        void propagateDrawObject(RGObj* newChild);
        void propagateRootObject(RGObj* newChild, bool addNames);
        void propagateAppObject(RGObj* newChild);

        string getName() const { return name; };
        void setName(const std::string& name);

        string getType() const;
        void setType(const std::string& type);

        void setDrawObject(RGDraw* newDrawObject);
        RGDraw* getDrawObject();                //!<returns a pointer to the drawing instance
        RGDraw* d();                            //!<returns a pointer to the drawing instance
        bool isDrawObjectValid();

        virtual void setEventHandler(RGEventHandlerBase* newEventHandler);

        void render(int XOffset, int YOffset, unsigned int milliSecondTimer);
        virtual void preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);
        virtual void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);

        //child and drag positions functions
        int getChildXRel2Self(int childIndex);
        int getChildYRel2Self(int childIndex);
        int getDragStartXRel2Self();
        int getDragStartYRel2Self();

        void resize(int newW, int newH);    //!<Sets width and height and notifies the object of the change


        RGObj* getParent();     //!<Returns a pointer to the parent object or nullptr
        RGApp* getApp();        //!<Returns a pointer to the app object or nullptr
        RGRoot* getRoot();      //!<Returns a pointer to the root object or nullptr

        void setParent(RGObj* newParent);
        void setApp(RGApp* newApp);
        void setRoot(RGRoot* newRoot);


    protected:


        RGEventHandlerBase* eventHandler;      //!<pointer to an event handler object

        virtual MouseDelegation drag(int mouseXin, int mouseYin, int button);
        virtual MouseDelegation press(int mouseXin, int mouseYin);
        virtual void release(int mouseXin, int mouseYin);



    private:
		vector <RGObj*> children;   //!<list of child objects

        RGObj* parent = nullptr;  //!<pointer to the parent object in the scene tree
        bool parentValid;   //!<is the pointer to the parent object valid

        RGRoot* rootObject = nullptr;     //!<pointer to the scene root object
        bool rootObjectValid;      //!<is the pointer to the scene root object valid

        RGApp* app = nullptr;     //!<pointer to the parent app object
        bool appValid;

        std::string name;    //!<object's short name
        std::string type;    //!<object's type

};


#endif // RGOBJ_H
