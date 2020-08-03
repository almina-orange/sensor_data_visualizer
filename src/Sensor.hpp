//
//  Sensor.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/03.
//

#ifndef Sensor_hpp
#define Sensor_hpp

#include "ofMain.h"


class Sensor {
    
    public:
        Sensor();
        void setBufferSize(int buffer_size);
        void pushAcc(float x, float y, float z);
        void pushGyro(float x, float y, float z);
        void clear();

        int max_buffer;
        vector<float> acc_x, acc_y, acc_z;
        vector<float> gyro_x, gyro_y, gyro_z;
};

#endif /* Sensor_hpp */
