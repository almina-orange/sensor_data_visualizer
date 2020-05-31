//
//  ViewSensor.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#include "ViewSensor.hpp"

//--------------------------------------------------------------
ViewSensor::ViewSensor(){
    drawMode = 0;
}

//--------------------------------------------------------------
void ViewSensor::load(){
    // read csv-file
    ofFileDialogResult result = ofSystemLoadDialog("Please select an audio file (.mp3, .wav, .aiff, .aac");
    if (result.bSuccess) { this->load(result.getPath()); }
}

//--------------------------------------------------------------
void ViewSensor::load(string filepath){
    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);
    
    // read csv-file
    csv.load(filepath);
    csv.removeRow(0);  // remove header

    setSensorObject(0);
    setDrawMode(0);
}

//--------------------------------------------------------------
void ViewSensor::update(){
    senObj.update();
}

//--------------------------------------------------------------
void ViewSensor::draw(ofRectangle r){
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    if (drawMode == 0) { senObj.draw3d(rs); }
    else if (drawMode == 1) { senObj.drawGraph(rs); }
    else if (drawMode == 2) { senObj.drawData(rs); }
}

//--------------------------------------------------------------
void ViewSensor::setSensorObject(int mode){
    ofFloatColor pal[4];
    pal[0] = ofFloatColor(0.0, 0.5, 1.0);
    pal[1] = ofFloatColor(1.0, 0.0, 0.5);
    pal[2] = ofFloatColor(1.0, 0.5, 0.0);
    pal[3] = ofFloatColor(0.5, 0.0, 1.0);

    int xi = mode * 3 + 1;
    int yi = mode * 3 + 2;
    int zi = mode * 3 + 3;
    ofVec3f *data = new ofVec3f[csv.getNumRows()];
    for (int i = 0; i < csv.getNumRows(); i++) {
        ofxCsvRow row = csv[i];
        data[i] = ofVec3f(row.getFloat(xi), row.getFloat(yi), row.getFloat(zi));
    }
    senObj.setup(data, csv.getNumRows(), pal[mode]);
}

//--------------------------------------------------------------
void ViewSensor::setDrawMode(int mode){
    drawMode = mode;
}