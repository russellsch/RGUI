#ifndef RGRADIOGROUP_H
#define RGRADIOGROUP_H

#include "RGObj.hpp"
#include "RGFrame.hpp"

#include <algorithm>

class RGToggle;

//!Group of radio buttons
/*!
This control is designed to hold toggle button objects. It encapsulates the adding and removing of objects so the user doesn't have to manage the
induvidual radio buttons (RGToggle) (use addItem).

This control has special methods to help ascertain which button is the one that is active.

This control can have a title. To use, add another paramater to the constructor for
the frame.



Example: \code
//without frame title
RGRadioGroup* togGrp1 = new RGRadioGroup("togglegroup1", 20,300, 70,90);
togGrp1->addItem("tog_a1", "Bananas");
togGrp1->addItem("tog_a2", "Lemons");
togGrp1->addItem("tog_a3", "Leopards");
root->addChild(togGrp1);

//with frame title
RGRadioGroup* togGrp2 = new RGRadioGroup("togglegroup1", 20,300, 70,90, "Choose:");
togGrp2->addItem("tog_b1", "Bananas");
togGrp2->addItem("tog_b2", "Lemons");
togGrp2->addItem("tog_b3", "Leopards");
root->addChild(togGrp2);
\endcode
*/
class DLLHELPER RGRadioGroup : public RGFrame
{
    public:
        RGRadioGroup(string name, int xNew, int yNew, int wNew, int hNew);
        RGRadioGroup(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);
        virtual ~RGRadioGroup();
        void addItem(string label); //!<Add a new radio button by label only, a name will be created from the label
        void addItem(string name, string label);    //!<Add a new radio button by name and label
        void release(int mouseXin, int mouseYin);

        void setAllChildrenOffExcept(int exceptIndex);    //!<Sets all children to off state except for the one with index exceptIndex
        void setAllChildrenOffExcept(RGToggle* exceptToggle);   //!<Sets all children to off state except for the one with the same pointer as exceptToggle
        int getActiveIndex();  //!Returns index of the active child (pressed radio button)
        bool isActiveByIndex(int index);  //!Returns whether the child radio button is activated or not
    protected:
        void updateChildPositions();
    private:
};

#endif // RGRADIOGROUP_H
