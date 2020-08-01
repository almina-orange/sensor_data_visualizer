//
//  ViewCsv.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/06.
//

#include "ViewCsv.hpp"

//--------------------------------------------------------------
void ViewCsv::load(){
    // read csv-file
    ofFileDialogResult result = ofSystemLoadDialog("Please select an audio file (.mp3, .wav, .aiff, .aac");
    if (result.bSuccess) { this->load(result.getPath()); }
}

//--------------------------------------------------------------
void ViewCsv::load(string filepath){
    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);
    
    // read csv-file
    this->filepath = filepath;
    csv.load(filepath);
    csv.removeRow(0);  // remove header
}

//--------------------------------------------------------------
void ViewCsv::update(){
    ofxCsvRow row = csv[frame];

    // att_x = m.getArgAsFloat(0);
    // att_y = m.getArgAsFloat(1);
    // att_z = m.getArgAsFloat(2);
    // att_w = m.getArgAsFloat(3);

    gyro_x = row.getFloat(4);
    gyro_y = row.getFloat(5);
    gyro_z = row.getFloat(6);

    grav_x = row.getFloat(7);
    grav_y = row.getFloat(8);
    grav_z = row.getFloat(9);

    acc_x = row.getFloat(10);
    acc_y = row.getFloat(11);
    acc_z = row.getFloat(12);
    
    // sensor.pushAtt(row.getFloat(1), row.getFloat(2), row.getFloat(3));
    sensor.pushGyro(gyro_x, gyro_y, gyro_z);
    sensor.pushGrav(grav_x, grav_y, grav_z);
    sensor.pushAcc(acc_x, acc_y, acc_z);

    setTargetData(viewDataIndex);

    frame = (frame + 1) % csv.getNumRows();
}

//--------------------------------------------------------------
void ViewCsv::draw(ofRectangle r){
    viewArea = r;
    
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    if (viewMode == 0) { draw3d(rs); }
    else if (viewMode == 1) { drawGraph(rs); }
    else if (viewMode == 2) { drawData(rs); }

    ofDrawBitmapStringHighlight(filepath, rs.x+20, rs.y+20, ofColor(0, 150));
}