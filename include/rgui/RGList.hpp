#ifndef RGLIST_H
#define RGLIST_H

#include "RGObj.hpp"


class DLLHELPER RGList : public RGObj
{
    public:
        RGList(string name, int xNew, int yNew, int wNew, int hNew);
        virtual ~RGList();

        void addChild(RGObj* newChild);

        float listPosYInPerc();

    protected:
        int listPosX, listPosY;
        int listW, listH;

        int listImgGrabPosX, listImgGrabPosY;

        int drag(int mouseXin, int mouseYin, int button);

        void updateChildPositions();
        void preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);
        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);


    private:
        void constrainListPos();
};

#endif // RGLIST_H
