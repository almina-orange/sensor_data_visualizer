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
        void pushGrav(float x, float y, float z);
        void pushGyro(float x, float y, float z);
        void pushAtt(float x, float y, float z, float w);

        int max_buffer;
        vector<float> acc_x, acc_y, acc_z;
        vector<float> grav_x, grav_y, grav_z;
        vector<float> gyro_x, gyro_y, gyro_z;
        vector<float> att_x, att_y, att_z, att_w;
};

#endif /* Sensor_hpp */
