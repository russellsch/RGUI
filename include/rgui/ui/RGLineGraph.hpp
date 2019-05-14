#ifndef RGLINEGRAPH_H
#define RGLINEGRAPH_H

#include "rgui/RGObj.hpp"
#include "rgui/ColorRGBA.hpp"

//!The internal component responsible for drawing line graphs
class RGLineGraph : public RGObj {
    public:
        RGLineGraph(string name, int xNew, int yNew, int wNew, int hNew);

        void load1DLineFromFloat(float* data, int points);  //!<Loads 1D line data from an array of floats
        void load1DLineFromInt(int* data, int points);    //!<Loads 1D line data from an array of ints
        void clearAllTraces();                              //!<Deletes all trace data

        ColorRGBA getDefaultColor(int lineNumber);

        MouseDelegation drag(int mouseXin, int mouseYin, MouseButton button);

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);

        float getXAxisMin();
        float getXAxisMax();
        float getYAxisMin();
        float getYAxisMax();

        void setMinMax(float xMin, float xMax, float yMin, float yMax);

        bool getTraceVisibility(unsigned int trace);
        void setTraceVisibility(unsigned int trace, bool visibility);
        //void setXAxisMin(float xAxisMinNew);

        virtual ~RGLineGraph();
    protected:
    private:
        vector< vector<float> > scaledTraces;     //array of array of floats, scaled to the current scale (alternates between x and y points), a trace referes to an array of 2d points

        //vector<RGColor> traceColors;

        vector<bool> traceVisibility;

        bool presetMinAndMax;   //min and max are preset so don't autoset them

        float xScale, yScale; // pixels/real
        bool viewHasChanged;



        float yAxisMin, yAxisMax;
        //float rightXAxisMin, rightXAxisMax;
        float xAxisMin, xAxisMax;

        int grabPosX, grabPosY;
        float grabXAxisMin, grabXAxisMax, grabYAxisMin, grabYAxisMax;



};

#endif // RGLINEGRAPH_H
