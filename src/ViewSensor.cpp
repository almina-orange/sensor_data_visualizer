//
//  ViewSensor.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#include "ViewSensor.hpp"

//--------------------------------------------------------------
ViewSensor::ViewSensor(){
    acc_x = 0;  acc_y = 0;  acc_z = 0;
    gyro_x = 0;  gyro_y = 0;  gyro_z = 0;

    tar_x = 0;  tar_y = 0;  tar_z = 0;
    tar_x_buf.assign(sensor.max_buffer, 0);
    tar_y_buf.assign(sensor.max_buffer, 0);
    tar_z_buf.assign(sensor.max_buffer, 0);

    frame = 0;
    viewMode = 0;
    viewDataIndex = 0;
    dataLabel = "acceleration";
    col = ofFloatColor(0.0, 0.5, 1.0);

    gui.setup();
    gui.add(range.setup("time range", sensor.max_buffer / 2, 0, sensor.max_buffer));
    gui.add(freq.setup("frequency", 50, 1, 100));
}

//--------------------------------------------------------------
void ViewSensor::load(){}

//--------------------------------------------------------------
void ViewSensor::update(){
    sensor.pushAcc(acc_x, acc_y, acc_z);
    sensor.pushGyro(gyro_x, gyro_y, gyro_z);

    frame++;

    setTargetData(viewDataIndex);
}

//--------------------------------------------------------------
void ViewSensor::draw(ofRectangle r){
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    if (viewMode == 0) { draw3d(rs); }
    else if (viewMode == 1) { drawGraph(rs); }
    else if (viewMode == 2) { drawData(rs); }

    gui.draw();
}

//--------------------------------------------------------------
void ViewSensor::drawData(ofRectangle r){
    ofDrawBitmapStringHighlight("frame = " + ofToString(frame), r.x + 20, r.y + r.height / 2 - 40, ofColor(0, 50));
    ofDrawBitmapStringHighlight(dataLabel + "_x: " + ofToString(tar_x), r.x+20, r.y+r.height/2-20, ofColor(0, 50));
    ofDrawBitmapStringHighlight(dataLabel + "_y: " + ofToString(tar_y), r.x+20, r.y+r.height/2   , ofColor(0, 50));
    ofDrawBitmapStringHighlight(dataLabel + "_z: " + ofToString(tar_z), r.x+20, r.y+r.height/2+20, ofColor(0, 50));
}

//--------------------------------------------------------------
void ViewSensor::drawGraph(ofRectangle r){
    ofDrawBitmapStringHighlight(dataLabel, r.x+20, r.y+r.height/2, ofColor(0, 150));

    ofMesh m_tar_x, m_tar_y, m_tar_z;
    m_tar_x.clear();  m_tar_x.setMode(OF_PRIMITIVE_LINE_STRIP);
    m_tar_y.clear();  m_tar_y.setMode(OF_PRIMITIVE_LINE_STRIP);
    m_tar_z.clear();  m_tar_z.setMode(OF_PRIMITIVE_LINE_STRIP);

    // Drawing graph "line"
    for (int i = 0; i < int(range); i++) {
        int td = ofMap(i, 0, int(range), r.x, r.x + r.width);
        int tx = ofMap(ofClamp(tar_x_buf[i], -3, 3), -3, 3, r.y + r.height, r.y);
        int ty = ofMap(ofClamp(tar_y_buf[i], -3, 3), -3, 3, r.y + r.height, r.y);
        int tz = ofMap(ofClamp(tar_z_buf[i], -3, 3), -3, 3, r.y + r.height, r.y);
        m_tar_x.addVertex(ofVec3f(td, tx));
        m_tar_y.addVertex(ofVec3f(td, ty));
        m_tar_z.addVertex(ofVec3f(td, tz));
    }
    
    ofSetColor(col);
    m_tar_x.draw();  m_tar_y.draw();  m_tar_z.draw();

    // Drawing graph "point"
    for (int i = 0; i < int(range); i++) {
        int td = ofMap(i, 0, int(range), r.x, r.x + r.width);
        int tx = ofMap(ofClamp(tar_x_buf[i], -3, 3), -3, 3, r.y + r.height, r.y);
        int ty = ofMap(ofClamp(tar_y_buf[i], -3, 3), -3, 3, r.y + r.height, r.y);
        int tz = ofMap(ofClamp(tar_z_buf[i], -3, 3), -3, 3, r.y + r.height, r.y);
        if ((frame + i) % int(freq) == 0) {
            ofSetColor(255, 150);
            ofDrawLine(td, r.y, td, r.y+r.height);
            ofDrawBitmapStringHighlight("f: " + ofToString(frame + i), ofMap(i, 0, int(range) - 1, r.x, r.x + r.width) + 5, r.y + r.height - 10);
            
            ofSetColor(col);
            ofNoFill();  ofDrawCircle(td, tx, 5);  ofDrawCircle(td, ty, 5);  ofDrawCircle(td, tz, 5);
            ofFill();    ofDrawCircle(td, tx, 3);  ofDrawCircle(td, ty, 3);  ofDrawCircle(td, tz, 3);

            ofDrawBitmapStringHighlight("x: " + ofToString(tar_x_buf[i]), td + 20, tx, ofColor(0, 50));
            ofDrawBitmapStringHighlight("y: " + ofToString(tar_y_buf[i]), td + 20, ty, ofColor(0, 50));
            ofDrawBitmapStringHighlight("z: " + ofToString(tar_z_buf[i]), td + 20, tz, ofColor(0, 50));
        }
    }
}

//--------------------------------------------------------------
void ViewSensor::draw3d(ofRectangle r){
    ofDrawBitmapStringHighlight(dataLabel, r.x+20, r.y+r.height/2, ofColor(0, 150));

    ofPushMatrix();
    ofTranslate(r.x, r.y);
    ofTranslate(r.width/2, r.height/2);
    ofScale((ofGetHeight() / r.height) / 5);
    ofRotateY(ofGetFrameNum()/4);

    ofSetColor(col);
    sensorObject.draw(tar_x, tar_y, tar_z);
    for (int i = 0; i < int(range); i++) {
        ofFill();
        drawCircleOnSphere(
            coord2lat(tar_x_buf[i], tar_y_buf[i], tar_z_buf[i]) / PI * 180,
            coord2lon(tar_x_buf[i], tar_y_buf[i], tar_z_buf[i]) / PI * 180,
            r.height,
            ofMap(i, 0, int(range)-1, 1, 10)
        );
        if (i > 0) {
            ofVec3f tv1 = ofVec3f(tar_x_buf[i-1], tar_y_buf[i-1], tar_z_buf[i-1]);
            ofVec3f tv2 = ofVec3f(tar_x_buf[i]  , tar_y_buf[i]  , tar_z_buf[i]  );
            ofDrawLine(tv1.normalized() * r.height, tv2.normalized() * r.height);
        }
    }
    ofVec3f tv = ofVec3f(tar_x, tar_y, tar_z);
    ofDrawLine(ofVec3f(0), tv.normalized() * r.height);

    ofPopMatrix();
}

//--------------------------------------------------------------
void ViewSensor::drawCircleOnSphere(float lat, float lon, float rad, float d){
    ofVec3f pos = ang2coord(lat, lon, rad);
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateZ(lon);
    ofRotateY(lat);
    ofDrawCircle(0, 0, d);
    ofPopMatrix();
}

//--------------------------------------------------------------
ofVec3f ViewSensor::ang2coord(float lat, float lon, float rad){
    ofQuaternion rotLat, rotLon;
    rotLat.makeRotate(lat, ofVec3f(0, 1, 0));
    rotLon.makeRotate(lon, ofVec3f(0, 0, 1));
    ofVec3f pos = ofVec3f(0, 0, rad);
    return rotLat * rotLon * pos;
}

//--------------------------------------------------------------
float ViewSensor::coord2lat(float x, float y, float z){
    return acos(z / sqrt(x * x + y * y + z * z));
}

//--------------------------------------------------------------
float ViewSensor::coord2lon(float x, float y, float z){
    float sign = y < 0 ? -1 : +1;
    return sign * acos(x / sqrt(x * x + y * y));
}

//--------------------------------------------------------------
void ViewSensor::setTargetData(int mode){
    if (mode == 0) {
        tar_x = acc_x; 
        tar_y = gyro_y;
        tar_z = acc_z;
        tar_x_buf = sensor.acc_x;
        tar_y_buf = sensor.acc_y;
        tar_z_buf = sensor.acc_z;
    } else if (mode == 1) {
        tar_x = gyro_x;
        tar_y = gyro_y;
        tar_z = gyro_z;
        tar_x_buf = sensor.gyro_x;
        tar_y_buf = sensor.gyro_y;
        tar_z_buf = sensor.gyro_z;
    }
}

//--------------------------------------------------------------
void ViewSensor::setSensorData(int mode){
    viewDataIndex = mode;

    if (mode == 0) { setDataLabel("acceleration"); }
    else if (mode == 1) { setDataLabel("gyro"); }
}

//--------------------------------------------------------------
void ViewSensor::setViewMode(int mode){
    viewMode = mode;
}

//--------------------------------------------------------------
void ViewSensor::setDataLabel(string label){
    dataLabel = label;
}

//--------------------------------------------------------------
void ViewSensor::setViewColor(ofColor col){
    this->col = col;
}
