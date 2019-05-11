#ifndef RGSPST_H
#define RGSPST_H


#include <string>

#include <RGObj.hpp>
#include <RGColor.hpp>

//!Simple button
class DLLHELPER RGButton : public RGObj {
    public:
        bool enabled;
        RGColor pressedColor;
        bool pressed;

        int style;

        bool verboseSPST;

        wstring label;

        RGButton(string name, int xNew, int yNew, int wNew, int hNew, wstring labelNew);
        RGButton(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);
        void preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);

        void setStyle(int styleNew);
        int getStyle();

        int press(int mouseXin, int mouseYin);
        void release(int mouseXin, int mouseYin);

        virtual ~RGButton();
    protected:
    private:
        string fontFile;
};

#endif // RGSPST_H
