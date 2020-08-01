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
        void draw(float roll, float pitch, float yaw);
};

#endif /* SensorObject_hpp */
