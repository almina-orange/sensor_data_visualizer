//
//  SensorObject.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/27.
//

#include "SensorObject.hpp"

//--------------------------------------------------------------
SensorObject::SensorObject(){
    frame = 0;
}

//--------------------------------------------------------------
void SensorObject::setup(ofVec3f *data, int num, ofFloatColor col){
    size = num;

    points = new ofVec3f[num];
    for (int i = 0; i < num; i++) { points[i] = data[i]; }

    // particle mesh setting
    objMesh.setMode(OF_PRIMITIVE_POINTS);

    static GLfloat distance[] = {0.0, 0.0, 1.0};
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
    glPointSize(1500);

    // ofFloatColor col = ofFloatColor(0.5, 0.5, 0.5);

    objMesh.clear();

    float rad = ofGetHeight() / 2.5;
    ofVec3f p;
    for (int i = 0; i < num; i++) {
        p = ofVec3f(0, 0, 1);
        p.rotateRad(data[i].x, ofVec3f(1, 0, 0));
        p.rotateRad(data[i].y, ofVec3f(0, 1, 0));
        p.rotateRad(data[i].z, ofVec3f(0, 0, 1));
        objMesh.addVertex(rad * p);
        objMesh.addColor(col);
    }
}

//--------------------------------------------------------------
void SensorObject::update(){
    frame++;
}

//--------------------------------------------------------------
void SensorObject::drawData(){
    ofDrawBitmapStringHighlight("x = " + ofToString(points[frame].x), 20, 20, ofColor(0, 50));
    ofDrawBitmapStringHighlight("y = " + ofToString(points[frame].x), 20, 40, ofColor(0, 50));
    ofDrawBitmapStringHighlight("z = " + ofToString(points[frame].x), 20, 60, ofColor(0, 50));
}

//--------------------------------------------------------------
void SensorObject::drawGraph(){
    ofSetColor(objMesh.getColor(0));

    ofNoFill();
    ofBeginShape();
    for (int i = 0; i < size; i++) { ofVertex(ofMap(i, 0, size-1, 10, ofGetWidth() - 10), points[i].x); }
    ofEndShape();

    ofNoFill();
    ofBeginShape();
    for (int i = 0; i < size; i++) { ofVertex(ofMap(i, 0, size-1, 10, ofGetWidth() - 10), points[i].y); }
    ofEndShape();
    
    ofNoFill();
    ofBeginShape();
    for (int i = 0; i < size; i++) { ofVertex(ofMap(i, 0, size-1, 10, ofGetWidth() - 10), points[i].z); }
    ofEndShape();
}

//--------------------------------------------------------------
void SensorObject::draw3d(){
    objMesh.drawWireframe();

    ofSetColor(objMesh.getColor(0));
    ofSpherePrimitive sphere;
    sphere.setRadius(4);
    sphere.setPosition(objMesh.getVertex(0));
    sphere.draw();
    ofDrawLine(ofVec3f(0), objMesh.getVertex(0));
}