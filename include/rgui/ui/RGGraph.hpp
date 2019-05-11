#ifndef RGGRAPH_H
#define RGGRAPH_H

#include "RGObj.hpp"
#include "RGLineGraph.hpp"

class RGGraph : public RGObj
{
    public:
        RGGraph(string name, int xNew, int yNew, int wNew, int hNew);
        virtual ~RGGraph();

        void load1DLineFromFloat(float* data, int points);
        void load1DLineFromInt(int* data, int points);
        void clearAllTraces();

        int drag(int mouseXin, int mouseYin, int button);

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);

        void setTitle(string titleNew);         //!<Sets the title of the graph
        void setXLabel(string xLabelNew);       //!<Sets the x label of the graph
        void setYLabel(string yLabelNew);       //!<Sets the y label of the graph

        void setXAxisPrecision(int precision);
        void setYAxisPrecision(int precision);

        bool getTraceVisibility(unsigned int trace);
        void setTraceVisibility(unsigned int trace, bool visibility);

        void setMinMax(float xMin, float xMax, float yMin, float yMax);

    protected:
        string xLabel, yLabel, title;
        int xAxisPrecision, yAxisPrecision;

        int borderTop, borderBottom, borderLeft, borderRight; //border between the edge and the graph area
        RGLineGraph* graph;

        RGTTF* fontTest;
    private:

};

#endif // RGGRAPH_H
