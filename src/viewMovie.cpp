//
//  ViewMovie.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#include "ViewMovie.hpp"

//--------------------------------------------------------------
ViewMovie::ViewMovie(){
    bViewMovieFile = true;
}

//--------------------------------------------------------------
void ViewMovie::load(string filepath){
    this->filepath = filepath;
    movie.load(filepath);
    movie.setLoopState(OF_LOOP_NORMAL);
    movie.play();

    camera.initGrabber(ofGetWidth(), ofGetHeight());

    frame = 0;
}

//--------------------------------------------------------------
void ViewMovie::load(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select an movie file (.mov, .mp4");
    if (result.bSuccess) { this->load(result.getPath()); }
}

//--------------------------------------------------------------
void ViewMovie::update(){
    movie.update();
    camera.update();
    frame++;
}

//--------------------------------------------------------------
void ViewMovie::draw(ofRectangle r){
    viewArea = r;
    
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    if (bViewMovieFile) {
        ofSetColor(255);
        // movie.setFrame(frame);
        movie.draw(rs.x, rs.y, rs.width, rs.height);
        
        float head = ofMap(movie.getPosition(), 0, 1, rs.x, rs.x+rs.width);
        ofDrawLine(head, rs.y, head, rs.y+rs.height);

        ofDrawBitmapStringHighlight(filepath, rs.x+20, rs.y+20, ofColor(0, 150));
    } else {
        ofSetColor(255);
        camera.draw(rs.x, rs.y, rs.width, rs.height);
    }
}

//--------------------------------------------------------------
void ViewMovie::switchInput(){
    bViewMovieFile = !(bViewMovieFile);
}

//--------------------------------------------------------------
void ViewMovie::switchPlaying(){
    movie.setPaused(movie.isPlaying());
}

//--------------------------------------------------------------
void ViewMovie::clear(){
    movie.stop();
}