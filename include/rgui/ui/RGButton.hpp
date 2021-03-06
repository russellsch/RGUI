#ifndef RGBUTTON_H
#define RGBUTTON_H


#include <string>

#include <rgui/RGObj.hpp>
#include <rgui/ColorRGBA.hpp>

//!Simple button
class RGButton : public RGObj {
    public:
        bool enabled;
        ColorRGBA pressedColor;
        bool pressed;

        int style;

        bool verboseSPST;

        wstring label;

        RGButton(string name, int xNew, int yNew, int wNew, int hNew, std::wstring label);
        //RGButton(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) override;
        void preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) override;

        void setStyle(int styleNew);
        int getStyle() { return style; };

        MouseDelegation press(int mouseXin, int mouseYin) override;
        void release(int mouseXin, int mouseYin) override;

        ~RGButton() = default;
    protected:
    private:
        string fontFile;
};

#endif // RGBUTTON_H
