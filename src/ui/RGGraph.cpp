#include "rgui/ui/RGGraph.hpp"

#include "GL/glew.h"

//Platform switch to allow getting the current working directory
//because microsoft breaks posix getcwd and renames it to _getcwd
//they also put it in a different header
#ifdef TARGET_WIN32_VC
    #include "direct.h"
    #define getcwd _getcwd
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#else
    #include "unistd.h"
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

RGGraph::RGGraph(string name, int xNew, int yNew, int wNew, int hNew): RGObj(name, "graph", xNew,yNew,wNew,hNew) {
    borderTop = 30;
    borderBottom = 20;
    borderLeft = 30;
    borderRight = 15;

    yAxisPrecision = 1;
    yAxisPrecision = 1;

    title = "It's a graph!";
    xLabel = "Spleens";
    yLabel = "Lemons";


    graph = new RGLineGraph(name+"lg1", borderLeft, borderTop, shape.getW() - borderLeft - borderRight,
            shape.getH() - borderTop - borderBottom);
    addChild(graph);

    fontTest = new RGTTF();
    fontTest->loadFont("data/wqy-microhei.ttc", 20);
    //fontTest->buildNormalChars();
}


void RGGraph::load1DLineFromFloat(float* data, int points) {
    graph->load1DLineFromFloat(data, points);
}

void RGGraph::load1DLineFromInt(int* data, int points) {
    graph->load1DLineFromInt(data, points);
}

void RGGraph::clearAllTraces() {
    graph->clearAllTraces();
}


MouseDelegation RGGraph::drag(int mouseXin, int mouseYin, MouseButton button) {
    MouseDelegation childrenDragResponse = RGObj::drag(mouseXin, mouseYin, button);

    if(childrenDragResponse == MouseDelegation::NOT_ACCEPTED){
        return MouseDelegation::THIS_ACCEPTED;
    }
    return childrenDragResponse;
}


void RGGraph::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    draw->pushMatrix();
    draw->translate(XOffset, YOffset);

    draw->stroke(0);
    draw->noFill();
    draw->rect(0, 0, shape.getW(), shape.getH() );

    draw->textSize(16);
    draw->text(title, (shape.getW()/2) - (draw->textWidth(title)/2), borderTop/2);
    draw->textSize(12);
    draw->text(xLabel, (shape.getW()/2) - (draw->textWidth(xLabel)/2), shape.getH() - borderBottom/2 + 3);

    draw->pushMatrix();
    draw->translate(borderLeft/2, (int)shape.getH()/2 + (draw->textWidth(yLabel)/2)  );
    draw->rotateDeg(-90);

    draw->text(yLabel, 0,0);
    draw->popMatrix();


    //draw axis labels
    draw->textSize(10);
    draw->text( toString(graph->getXAxisMin(), xAxisPrecision), borderLeft, shape.getH() - borderBottom/2);
    draw->text( toString(graph->getXAxisMax(), xAxisPrecision),
            shape.getW() - draw->textWidth(toString(graph->getXAxisMax(), xAxisPrecision)) - 5,
            shape.getH() - borderBottom/2);

    draw->text( toString(graph->getYAxisMax(),yAxisPrecision), -1, borderTop - 2);
    draw->text( toString(graph->getYAxisMin(),yAxisPrecision), -1, shape.getH() - borderBottom + 2);

    draw->textSize(12);

    //fontTest->drawCharacter(22, 0,0);
    draw->fill(0);
    //wstring testString = L"12e3g56 Poodle \nKableて　漢字";
	//wstring testString = L"test test";

    //draw->fonts2[10].drawString(testString, -100,-100);

    //draw->stroke(0);
    //draw->fill(0);
    //fontTest->drawString(testString, 0,-40, textColor);

    //draw->stroke(0);
    //draw->line(0,-40, 100,-40);
    //draw->line(0,-40, 0,0);


    //draw->textSize(20);
    //draw->text( "123456", 0,-60);

    /*draw->noFill();
    draw->stroke(0,0,255);
    pair<int, int> bb = fontTest->boundingDims(testString);
    RGBB bb2 = fontTest->boundingBox(testString);
    draw->rect(bb2.x,bb2.y-40, bb2.width, bb2.height);*/


    glPopMatrix();

}

void RGGraph::setTitle(string titleNew) {
    title = titleNew;
}
void RGGraph::setXLabel(string xLabelNew) {
    xLabel = xLabelNew;
}
void RGGraph::setYLabel(string yLabelNew) {
    yLabel = yLabelNew;
}


void RGGraph::setXAxisPrecision(int precision){
    xAxisPrecision = precision;
}

void RGGraph::setYAxisPrecision(int precision){
    yAxisPrecision = precision;
}


bool RGGraph::getTraceVisibility(unsigned int trace) {
    return graph->getTraceVisibility(trace);
}
void RGGraph::setTraceVisibility(unsigned int trace, bool visibility){
    graph->setTraceVisibility(trace, visibility);
}

void RGGraph::setMinMax(float xMin, float xMax, float yMin, float yMax){
    graph->setMinMax(xMin, xMax, yMin, yMax);
}
