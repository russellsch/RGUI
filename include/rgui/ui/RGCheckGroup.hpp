#ifndef RGCHECKGROUP_H
#define RGCHECKGROUP_H

#include <rgui/ui/RGFrame.hpp>

#include <vector>
#include <algorithm>

//!Group of check buttons

class DLLHELPER RGCheckGroup : public RGFrame {
public:
    RGCheckGroup(string name, int xNew, int yNew, int wNew, int hNew);
    RGCheckGroup(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);

    void addItem(string label); //!<Add a new check button by label only, a name will be created from the label
    void addItem(string name, string label);    //!<Add a new check button by name and label
    void addItem(string name, string label, bool state);    //!<Add a new check button by name and label and a given state
    void release(int mouseXin, int mouseYin);

    vector<int> getActiveIndexes();  //!Returns indexes of the active children (pressed check buttons), in vector<int>
    bool isActiveByIndex(int index);  //!Returns whether the child radio button is activated or not

    void setHorizontalPacking();    //!Temporary hack to enable horizontal packing until we get an official packing system setup
protected:
    void updateChildPositions();        //!Recalculates vertical spacing of all children (this will be replaced by more advanced packing functions later)
    void updateChildPositionsHoriz();   //!Recalculates horizontal spacing of all children (this will be replaced by more advanced packing functions later)

    bool packVertical;                  //!Should children be packed vertically? (or horizontally)
private:
};

#endif // RGCHECKGROUP_H
