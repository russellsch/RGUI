#ifndef RGTOGGLE_H
#define RGTOGGLE_H

#include "rgui/RGObj.hpp"

//!Multi-purpose toggle object
/*!
This object has two states, on and off. Various visual styles allow it to appear as a button, a slider (like on an iphone)
, a checkbox, a radio button, etc...
*/
class RGToggle : public RGObj {
    public:
        bool value;
        int style;
        string label;
        bool verboseToggle;

        RGToggle(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);
        ~RGToggle() = default;

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) override;
        void toggle();

        MouseDelegation press(int mouseXin, int mouseYin) override;
        void release(int mouseXin, int mouseYin) override;

        void setOff();
        void setOn();
        void setStyle(int styleNew);

        bool getValue();
    protected:
    private:
};

#endif // RGTOGGLE_H
