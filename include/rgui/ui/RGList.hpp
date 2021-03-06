#ifndef RGLIST_H
#define RGLIST_H

#include "rgui/RGObj.hpp"


class RGList : public RGObj
{
    public:
        RGList(string name, int xNew, int yNew, int wNew, int hNew);
        ~RGList() = default;

        void addChild(RGObj* newChild);

        float listPosYInPerc();

    protected:
        int listPosX, listPosY;
        int listW, listH;

        int listImgGrabPosX, listImgGrabPosY;

        MouseDelegation drag(int mouseXin, int mouseYin, MouseButton button) override ;

        void updateChildPositions();
        void preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) override ;
        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) override ;


    private:
        void constrainListPos();
};

#endif // RGLIST_H
