//
//  SensorObject.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/27.
//

#include "SensorObject.hpp"

//--------------------------------------------------------------
SensorObject::SensorObject(){}

//--------------------------------------------------------------
void SensorObject::draw(float roll, float pitch, float yaw){
    ofBoxPrimitive box;
    box.set(50, 100, 10);
    box.setResolution(4, 8, 1);
    box.rotateRad(roll , ofVec3f(1, 0, 0));
    box.rotateRad(pitch, ofVec3f(0, 1, 0));
    box.rotateRad(yaw  , ofVec3f(0, 0, 1));
    box.drawWireframe();
}
