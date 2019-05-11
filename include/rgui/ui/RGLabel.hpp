#ifndef RGLABEL_H
#define RGLABEL_H

#include "RGObj.hpp"

//!Simple text label
class RGLabel : public RGObj {
    public:
        RGLabel(string name, int xNew, int yNew, int wNew, int hNew);
        virtual ~RGLabel();
    protected:


        unsigned int justification;         //0-left, 1-center, 2-right



    private:
};



#endif // RGLABEL_H
