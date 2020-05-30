//
//  SensorObject.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/27.
//

#ifndef SensorObject_hpp
#define SensorObject_hpp

#include "ofMain.h"

class SensorObject {
    
    public:
        SensorObject();
        void setup(ofVec3f *data, int num, ofFloatColor col);
        void update();
        void drawData(ofRectangle r);
        void drawGraph(ofRectangle r);
        void draw3d(ofRectangle r);

        int size;
        ofVboMesh objMesh;
        ofVec3f *points;

        int frame;
};

#endif /* SensorObject_hpp */
