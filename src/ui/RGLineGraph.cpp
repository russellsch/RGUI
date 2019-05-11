#include "RGLineGraph.hpp"
#include "RGApp.hpp"

RGLineGraph::RGLineGraph(string name, int xNew, int yNew, int wNew, int hNew): RGObj(name, "linegraph", xNew,yNew,wNew,hNew) {
    viewHasChanged = true;
    presetMinAndMax = false;
    //ctor
}

RGLineGraph::~RGLineGraph()
{


}


//void RGLineGraph::load1DLineFromFloat(float* data, int points, float xMin, float xMax, float yMin, float yMax)
//void RGLineGraph::load1DLineFromUShort(unsigned short* data, int points, unsigned short xMin, unsigned short xMax, unsigned short yMin, unsigned short yMax)

void RGLineGraph::load1DLineFromFloat(float* data, int points) {
    vector<float> scaledData;

    if(scaledTraces.size() == 0) {
        if( !presetMinAndMax) {
            //find data min and max for first trace only
            float minPt, maxPt;
            minPt = data[0];
            maxPt = data[0];
            for(int i=1; i<points; i++){
                if(data[i] < minPt ) { minPt = data[i]; }
                if(data[i] > maxPt ) { maxPt = data[i]; }
            }
            //determine the axes automatically in real units
            yAxisMin = minPt;
            yAxisMax = maxPt;

            xAxisMin = 0;
            xAxisMax = points;
        }

        //determine the scaling ratio so the data fits within the axes
        xScale = (float)getW()/(float)( abs((int)(xAxisMax-xAxisMin)) );
        yScale = -(float)getH()/(float)( abs((int)(yAxisMax-yAxisMin)) );
    }

    cout << endl<< "yreal min:" << yAxisMin << "max:" << yAxisMax << endl;
    cout << "xreal min:" << xAxisMin << "max:" << xAxisMax << endl;
    cout << "xscale: " <<  xScale << "yscale:" << yScale << " w:" <<  getW() << " h:" <<  getH() << endl;

    //load and scale the data into scaledPoints, adding the y coordinate automatically since this is 1D data
    for(int i=0; i<points; i++){
        scaledData.push_back( i*xScale );
        scaledData.push_back( data[i]*yScale );
    }

    scaledTraces.push_back(scaledData);

    traceVisibility.push_back(true);


}

void RGLineGraph::load1DLineFromInt(int* data, int points) {
    vector<float> scaledData;

    if(scaledTraces.size() == 0 ) {
        if( !presetMinAndMax) {
            //find data min and max for first trace only
            int minPt, maxPt;
            minPt = data[0];
            maxPt = data[0];
            for(int i=1; i<points; i++){
                if(data[i] < minPt ) { minPt = data[i]; }
                if(data[i] > maxPt ) { maxPt = data[i]; }
            }
            //determine the axes automatically in real units
            yAxisMin = (float)minPt;
            yAxisMax = (float)maxPt;

            xAxisMin = 0;
            xAxisMax = points;
        }

        //determine the scaling ratio so the data fits within the axes
        xScale = (float)getW()/(float)( abs((int)(xAxisMax-xAxisMin)) );
        yScale = -(float)getH()/(float)( abs((int)(yAxisMax-yAxisMin)) );
    }

    cout << endl<< "yreal min:" << yAxisMin << "max:" << yAxisMax << endl;
    cout << "xreal min:" << xAxisMin << "max:" << xAxisMax << endl;
    cout << "xscale: " <<  xScale << "yscale:" << yScale << " w:" <<  getW() << " h:" <<  getH() << endl;

    //load and scale the data into scaledPoints, adding the y coordinate automatically since this is 1D data
    for(int i=0; i<points; i++){
        scaledData.push_back( i*xScale );
        scaledData.push_back( data[i]*yScale );
    }

    scaledTraces.push_back(scaledData);

    traceVisibility.push_back(true);


}


void RGLineGraph::clearAllTraces() {
    scaledTraces.clear();
    traceVisibility.clear();
}

RGColor RGLineGraph::getDefaultColor(int lineNumber) {
    if(lineNumber == 0) {
        return RGColor(0,0,255);
    } else if(lineNumber == 1) {
        return RGColor(0,200,0);
    } else if(lineNumber == 2) {
        return RGColor(150,0,0);
    } else if(lineNumber == 3) {
        return RGColor(150,150,0);
    } else {
        return RGColor(rand()*255,rand()*255,rand()*255);
    }

}

int RGLineGraph::drag(int mouseXin, int mouseYin, int button) {
    //cout << "Graph drag mousex " << mouseXin << "mousey" << mouseYin << " DragstartX " << dragStartX << "DragStartY" << dragStartY << endl;
    int childrenDragResponse = RGObj::drag(mouseXin, mouseYin, button);

    if(initialDrag) {   //keep track of where the drag started from
        grabXAxisMin = xAxisMin;
        grabXAxisMax = xAxisMax;
        grabYAxisMin = yAxisMin;
        grabYAxisMax = yAxisMax;
    }
    if(button == 2){    //right mousebutton drags
        if(childrenDragResponse == 0){
            xAxisMin = grabXAxisMin -(mouseXin - dragStartX)/xScale;
            xAxisMax = grabXAxisMax -(mouseXin - dragStartX)/xScale;

            yAxisMin = grabYAxisMin-(mouseYin - dragStartY)/yScale;
            yAxisMax = grabYAxisMax-(mouseYin - dragStartY)/yScale;

            viewHasChanged = true;
            //cout << "Graph drag ymin " << yAxisMin << " ymax " << yAxisMax <<endl;
            return 1;
        }
    }

    return childrenDragResponse;
}


void RGLineGraph::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    draw->stroke(0);
    draw->fill(255);
    draw->rect(XOffset, YOffset, getW(), getH() );

    glEnable(GL_SCISSOR_TEST);
    int clipY = getApp()->getWindowH() - YOffset - getH();
    glScissor(XOffset, clipY, getW(), getH());

    draw->pushMatrix();
    //draw->translate(XOffset, YOffset);
    draw->translate(XOffset - (xAxisMin*xScale), YOffset + (yAxisMin*yScale) - ((yAxisMin+yAxisMax)*yScale) );


    for(int i=0; i<scaledTraces.size(); i++){   //itterate through all traces
        if(traceVisibility.at(i)) {     //is the trace set to visible?
            RGColor traceColor = getDefaultColor(i);
            glColor4ub(traceColor.r,traceColor.g,traceColor.b,traceColor.a);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, 0, &scaledTraces[i][0]);
            glDrawArrays(GL_LINE_STRIP, 0, scaledTraces[i].size()/2);
        }
    }
    /*glColor4ub(0,0,255,255);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, &scaledTraces[0][0]);
    glDrawArrays(GL_LINE_STRIP, 0, scaledTraces[0].size()/2);*/

    draw->popMatrix();
    glDisable(GL_SCISSOR_TEST);
}


float RGLineGraph::getXAxisMin(){
    return xAxisMin;
}
float RGLineGraph::getXAxisMax(){
    return xAxisMax;
}
float RGLineGraph::getYAxisMin(){
    return yAxisMin;
}
float RGLineGraph::getYAxisMax(){
    return yAxisMax;
}

void RGLineGraph::setMinMax(float xMin, float xMax, float yMin, float yMax) {
    xAxisMin = xMin;
    yAxisMin = yMin;
    xAxisMax = xMax;
    yAxisMax = yMax;
    presetMinAndMax = true;
}


bool RGLineGraph::getTraceVisibility(unsigned int trace) {
    if(trace< traceVisibility.size()) { return false;}
    return traceVisibility.at(trace);
}
void RGLineGraph::setTraceVisibility(unsigned int trace, bool visibility) {
    //if(trace< traceVisibility.size()) { return;}
    traceVisibility[trace] = visibility;
}

