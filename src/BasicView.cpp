//
//  BasicView.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/06.
//

#include "BasicView.hpp"

//--------------------------------------------------------------
BasicView::BasicView(){
    frame = 0;
}

//--------------------------------------------------------------
void BasicView::load(){}

//--------------------------------------------------------------
void BasicView::update(){
    frame++;
}

//--------------------------------------------------------------
void BasicView::draw(ofRectangle r){
    viewArea = r;

    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);
    ofDrawBitmapStringHighlight(ofToString(frame), rs.x+20, rs.y+20);
}

//--------------------------------------------------------------
bool BasicView::onMouse(int x, int y){
    return viewArea.inside(x, y);
}