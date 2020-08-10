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
    frame = 0;
    f_frame = 0.0;

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
void ViewCsv::drawGraph(ofRectangle r) {
    ofDrawBitmapStringHighlight(dataLabel, r.x+20, r.y+r.height/2, ofColor(0, 150));

    ofMesh m_tar_x, m_tar_y, m_tar_z;
    m_tar_x.clear();  m_tar_x.setMode(OF_PRIMITIVE_LINE_STRIP);
    m_tar_y.clear();  m_tar_y.setMode(OF_PRIMITIVE_LINE_STRIP);
    m_tar_z.clear();  m_tar_z.setMode(OF_PRIMITIVE_LINE_STRIP);

    // head index
    int head = sensor.max_buffer - frame - 1;
    if (head < sensor.max_buffer - int(range)) { head = sensor.max_buffer - int(range); }

    // Drawing graph "line"
    for (int i = 0; i < int(range); i++) {
        if (head + i > sensor.max_buffer) { break; }
        int td = ofMap(i, 0, int(range), r.x, r.x + r.width);
        int tx = ofMap(ofClamp(tar_x_buf[head + i], -3, 3), -3, 3, r.y + r.height, r.y);
        int ty = ofMap(ofClamp(tar_y_buf[head + i], -3, 3), -3, 3, r.y + r.height, r.y);
        int tz = ofMap(ofClamp(tar_z_buf[head + i], -3, 3), -3, 3, r.y + r.height, r.y);
        m_tar_x.addVertex(ofVec3f(td, tx));
        m_tar_y.addVertex(ofVec3f(td, ty));
        m_tar_z.addVertex(ofVec3f(td, tz));
    }

    ofSetColor(col);
    m_tar_x.draw();  m_tar_y.draw();  m_tar_z.draw();

    // Drawing graph "point"
    for (int i = 0; i < int(range); i++) {
        if (head + i > sensor.max_buffer) { break; }
        int td = ofMap(i, 0, int(range), r.x, r.x + r.width);
        int tx = ofMap(ofClamp(tar_x_buf[head + i], -3, 3), -3, 3, r.y + r.height, r.y);
        int ty = ofMap(ofClamp(tar_y_buf[head + i], -3, 3), -3, 3, r.y + r.height, r.y);
        int tz = ofMap(ofClamp(tar_z_buf[head + i], -3, 3), -3, 3, r.y + r.height, r.y);

        int frame_idx = frame - int(range) + i;
        if (frame < int(range)) { frame_idx = i; }

        if (frame_idx % int(freq) == 0) {
            ofSetColor(255, 150);
            ofDrawLine(td, r.y, td, r.y+r.height);
            ofDrawBitmapStringHighlight("f: " + ofToString(frame_idx), ofMap(i, 0, int(range) - 1, r.x, r.x + r.width) + 5, r.y + r.height - 10);

            // ofSetColor(col);
            // ofNoFill();  ofDrawCircle(td, tx, 5);  ofDrawCircle(td, ty, 5);  ofDrawCircle(td, tz, 5);
            // ofFill();    ofDrawCircle(td, tx, 3);  ofDrawCircle(td, ty, 3);  ofDrawCircle(td, tz, 3);

            // ofDrawBitmapStringHighlight("x: " + ofToString(tar_x_buf[head + i]), td + 20, tx, ofColor(0, 50));
            // ofDrawBitmapStringHighlight("y: " + ofToString(tar_y_buf[head + i]), td + 20, ty, ofColor(0, 50));
            // ofDrawBitmapStringHighlight("z: " + ofToString(tar_z_buf[head + i]), td + 20, tz, ofColor(0, 50));
        }
    }
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