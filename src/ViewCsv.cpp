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

    bPlaying = true;

    gui.setup();
    gui.add(range.setup("time range", sensor.max_buffer / 2, 0, sensor.max_buffer));
    gui.add(freq.setup("frequency", 50, 1, 100));
}

//--------------------------------------------------------------
void ViewCsv::update(){
    if (bPlaying) {
        ofxCsvRow row = csv[frame];

        acc_x = row.getFloat(1);
        acc_y = row.getFloat(2);
        acc_z = row.getFloat(3);

        gyro_x = row.getFloat(4);
        gyro_y = row.getFloat(5);
        gyro_z = row.getFloat(6);
        
        sensor.pushAcc(acc_x, acc_y, acc_z);
        sensor.pushGyro(gyro_x, gyro_y, gyro_z);

        frame = (frame + 1) % csv.getNumRows();
    }

    setTargetData(viewDataIndex);
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

    gui.draw();

    ofDrawBitmapStringHighlight(filepath, rs.x+20, rs.y+20, ofColor(0, 150));
}

//--------------------------------------------------------------
void ViewCsv::switchPlaying(){
    bPlaying = !bPlaying;
}

//--------------------------------------------------------------
void ViewCsv::clear(){
    sensor.clear();

    tar_x = 0;  tar_y = 0;  tar_z = 0;
    tar_x_buf.assign(sensor.max_buffer, 0);
    tar_y_buf.assign(sensor.max_buffer, 0);
    tar_z_buf.assign(sensor.max_buffer, 0);

    frame = 0;
    bPlaying = false;
}