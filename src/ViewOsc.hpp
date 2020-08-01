//
//  ViewOsc.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/03.
//

#ifndef ViewOsc_hpp
#define ViewOsc_hpp

#include "ofMain.h"
#include "ViewSensor.hpp"

#include "ofxOsc.h"
#include "SensorObject.hpp"
#include "Sensor.hpp"

#define PORT 12345
// #define UUID "CZkvJ_-J2vK0q0IH"
// #define UUID "C1444UG6Ntbq_DVf"
#define UUID "sbiphone"

class ViewOsc : public ViewSensor {
    
    public:
        void load();
        void update();
        void draw(ofRectangle r);

        ofxOscReceiver receiver;
        string deviceInfo;
};

#endif /* ViewOsc_hpp */
