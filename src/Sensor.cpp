//
//  Sensor.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/03.
//

#include "Sensor.hpp"

//--------------------------------------------------------------
Sensor::Sensor(){
    max_buffer = 200;
    acc_x.assign(max_buffer, 0);
    acc_y.assign(max_buffer, 0);
    acc_z.assign(max_buffer, 0);
    grav_x.assign(max_buffer, 0);
    grav_y.assign(max_buffer, 0);
    grav_z.assign(max_buffer, 0);
    gyro_x.assign(max_buffer, 0);
    gyro_y.assign(max_buffer, 0);
    gyro_z.assign(max_buffer, 0);
    att_x.assign(max_buffer, 0);
    att_y.assign(max_buffer, 0);
    att_z.assign(max_buffer, 0);
    att_w.assign(max_buffer, 0);
}

//--------------------------------------------------------------
void Sensor::setBufferSize(int buffer_size){
    max_buffer = buffer_size;
    acc_x.assign(max_buffer, 0);
    acc_y.assign(max_buffer, 0);
    acc_z.assign(max_buffer, 0);
    grav_x.assign(max_buffer, 0);
    grav_y.assign(max_buffer, 0);
    grav_z.assign(max_buffer, 0);
    gyro_x.assign(max_buffer, 0);
    gyro_y.assign(max_buffer, 0);
    gyro_z.assign(max_buffer, 0);
    att_x.assign(max_buffer, 0);
    att_y.assign(max_buffer, 0);
    att_z.assign(max_buffer, 0);
    att_w.assign(max_buffer, 0);
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
void Sensor::pushGrav(float x, float y, float z){
    grav_x.push_back(x);
    grav_y.push_back(y);
    grav_z.push_back(z);
    if (grav_x.size() >= max_buffer) {
        grav_x.erase(grav_x.begin(), grav_x.begin()+1);
        grav_y.erase(grav_y.begin(), grav_y.begin()+1);
        grav_z.erase(grav_z.begin(), grav_z.begin()+1);
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
void Sensor::pushAtt(float x, float y, float z, float w){
    att_x.push_back(x);
    att_y.push_back(y);
    att_z.push_back(z);
    att_w.push_back(w);
    if (att_x.size() >= max_buffer) {
        att_x.erase(att_x.begin(), att_x.begin()+1);
        att_y.erase(att_y.begin(), att_y.begin()+1);
        att_z.erase(att_z.begin(), att_z.begin()+1);
        att_w.erase(att_w.begin(), att_w.begin()+1);
    }
}