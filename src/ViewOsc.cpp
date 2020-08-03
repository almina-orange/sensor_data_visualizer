//
//  ViewOsc.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/03.
//

#include "ViewOsc.hpp"

//--------------------------------------------------------------
void ViewOsc::load(){
    ofLog() << "listening for osc messages on port " << PORT;
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ViewOsc::update(){
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);

        // cout << m.getAddress() << endl;

        string address = string("/ZIGSIM/") + UUID;

        if (m.getAddress() == address + "/deviceinfo") {
            deviceInfo = m.getArgAsString(0);
        } else if (m.getAddress() == address + "/accel") {
            acc_x = m.getArgAsFloat(0);
            acc_y = m.getArgAsFloat(1);
            acc_z = m.getArgAsFloat(2);
        } else if (m.getAddress() == address + "/gyro") {
            gyro_x = m.getArgAsFloat(0);
            gyro_y = m.getArgAsFloat(1);
            gyro_z = m.getArgAsFloat(2);
        }
    }

    sensor.pushAcc(acc_x, acc_y, acc_z);
    sensor.pushGyro(gyro_x, gyro_y, gyro_z);

    setTargetData(viewDataIndex);

    frame++;
}

//--------------------------------------------------------------
void ViewOsc::draw(ofRectangle r){
    viewArea = r;
    
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(0, 255, 0);   ofDrawRectangle(rs);

    if (viewMode == 0) { draw3d(rs); }
    else if (viewMode == 1) { drawGraph(rs); }
    else if (viewMode == 2) { drawData(rs); }

    ofDrawBitmapStringHighlight(deviceInfo, rs.x+20, rs.y+20, ofColor(0, 150));
}
