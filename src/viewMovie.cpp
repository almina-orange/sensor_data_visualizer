//
//  ViewMovie.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#include "ViewMovie.hpp"

//--------------------------------------------------------------
ViewMovie::ViewMovie(){

}

//--------------------------------------------------------------
void ViewMovie::load(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select an movie file (.mov, .mp4");
    if (result.bSuccess) { this->load(result.getPath()); }
}

//--------------------------------------------------------------
void ViewMovie::load(string filepath){
    movie.load(filepath);
    movie.setLoopState(OF_LOOP_NORMAL);
    movie.play();
}

//--------------------------------------------------------------
void ViewMovie::update(){
    movie.update();
}

//--------------------------------------------------------------
void ViewMovie::draw(ofRectangle r){
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    ofSetColor(255);
    movie.draw(rs.x, rs.y, rs.width, rs.height);
}
