//
//  Sensor.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/03.
//

#include "Sensor.hpp"

//--------------------------------------------------------------
Sensor::Sensor(){
    max_buffer = 400;
    acc_x.assign(max_buffer, 0);
    acc_y.assign(max_buffer, 0);
    acc_z.assign(max_buffer, 0);
    gyro_x.assign(max_buffer, 0);
    gyro_y.assign(max_buffer, 0);
    gyro_z.assign(max_buffer, 0);
}

//--------------------------------------------------------------
void Sensor::setBufferSize(int buffer_size){
    max_buffer = buffer_size;
    acc_x.assign(max_buffer, 0);
    acc_y.assign(max_buffer, 0);
    acc_z.assign(max_buffer, 0);
    gyro_x.assign(max_buffer, 0);
    gyro_y.assign(max_buffer, 0);
    gyro_z.assign(max_buffer, 0);
}

//--------------------------------------------------------------
void Sensor::pushAcc(float x, float y, float z){
    acc_x.push_back(x);
    acc_y.push_back(y);
    acc_z.push_back(z);
    if (acc_x.size() >= max_buffer) {
        acc_x.erase(acc_x.begin(), acc_x.begin()+1);
        acc_y.erase(acc_y.begin(), acc_y.begin()+1);
        acc_z.erase(acc_z.begin(), acc_z.begin()+1);
    }
}

//--------------------------------------------------------------
void Sensor::pushGyro(float x, float y, float z){
    gyro_x.push_back(x);
    gyro_y.push_back(y);
    gyro_z.push_back(z);
    if (gyro_x.size() >= max_buffer) {
        gyro_x.erase(gyro_x.begin(), gyro_x.begin()+1);
        gyro_y.erase(gyro_y.begin(), gyro_y.begin()+1);
        gyro_z.erase(gyro_z.begin(), gyro_z.begin()+1);
    }
}

//--------------------------------------------------------------
void Sensor::clear(){
    acc_x.assign(max_buffer, 0);
    acc_y.assign(max_buffer, 0);
    acc_z.assign(max_buffer, 0);
    gyro_x.assign(max_buffer, 0);
    gyro_y.assign(max_buffer, 0);
    gyro_z.assign(max_buffer, 0);
}