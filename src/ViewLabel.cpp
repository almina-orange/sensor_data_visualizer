//
//  ViewLabel.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#include "ViewLabel.hpp"

//--------------------------------------------------------------
void ViewLabel::draw(ofRectangle r){
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    ofSetColor(255);
    // example bar graph
    ofFill();
    for (int i = 0; i < 8; i++) {
        ofDrawRectangle(
            rs.x,
            ofMap(i, 0, 8, rs.y, rs.y+rs.height),
            rs.width - ofRandom(rs.width),
            rs.height / 8 * 0.5
        );
    }
}
