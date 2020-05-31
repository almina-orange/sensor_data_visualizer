//
//  ViewSensor.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#ifndef ViewSensor_hpp
#define ViewSensor_hpp

#include "ofMain.h"

#include "ofxCsv.h"
#include "SensorObject.hpp"

class ViewSensor {
    
    public:
        ViewSensor();
        void load();
        void load(string filepath);
        void update();
        void draw(ofRectangle r);

        void setSensorObject(int mode);
        void setDrawMode(int mode);

        ofxCsv csv;
        SensorObject senObj;
        int drawMode;
};

#endif /* ViewSensor_hpp */
