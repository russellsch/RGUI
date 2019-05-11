#ifndef RGBUTTON_H
#define RGBUTTON_H


#include <string>

#include <rgui/RGObj.hpp>
#include <rgui/RGColor.hpp>

//!Simple button
class RGButton : public RGObj {
    public:
        bool enabled;
        RGColor pressedColor;
        bool pressed;

        int style;

        bool verboseSPST;

        wstring label;

        RGButton(string name, int xNew, int yNew, int wNew, int hNew, std::wstring labelNew);
        //RGButton(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);
        void preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);

        void setStyle(int styleNew);
        int getStyle() { return style; };

        int press(int mouseXin, int mouseYin);
        void release(int mouseXin, int mouseYin);

        virtual ~RGButton();
    protected:
    private:
        string fontFile;
};

#endif // RGBUTTON_H
