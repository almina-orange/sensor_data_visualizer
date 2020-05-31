#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofApp");
    
    ofSetFrameRate(50);
    ofBackground(0);
    ofSetCircleResolution(32);
    // ofEnableDepthTest();
    // ofEnableSmoothing();

    // viewSensor.load();
    // viewMovie.load();
    // viewAudio.load();
    // viewLabel.load();

    viewSensor.load("2020-0427-134121.csv");
    viewMovie.load("fingers.mov");
    viewAudio.load("/Users/almina/Downloads/of_v0.10.0_osx_release/apps/myApps/sensor_data_visualizer/bin/data/beat.wav");
    viewLabel.load();

    bSwitch = true;
    bViewInfo = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    viewMovie.update();
    viewAudio.update();
    viewSensor.update();
    viewLabel.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSeedRandom(0);

    if (bSwitch) { separatedWindow(); }
    else { duplicatedWindow(); }

    ofDrawBitmapStringHighlight("[h]: view info", 20, 20);
    if (bViewInfo) {
        ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate()), 20, 40);
        ofDrawBitmapStringHighlight("[spqce]: switch window mode (dup/sep)", 20, 60);
        ofDrawBitmapStringHighlight("[1..4]: switch sensor data (att/gyro/grav/acc)", 20, 80);
        ofDrawBitmapStringHighlight("[q/w/e]: switch sensor data style", 20, 100);
    }
}

//--------------------------------------------------------------
void ofApp::separatedWindow(){
    viewMovie.draw(ofRectangle(0, 0, ofGetWidth()/2, ofGetHeight()/2));
    viewAudio.draw(ofRectangle(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2));
    viewSensor.draw(ofRectangle(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2));
    viewLabel.draw(ofRectangle(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2));
}

//--------------------------------------------------------------
void ofApp::duplicatedWindow(){
    viewMovie.draw(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    viewAudio.draw(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    viewSensor.draw(ofRectangle(ofGetWidth()/2, ofGetHeight()/4, ofGetWidth()/2, ofGetHeight()/2));
    viewLabel.draw(ofRectangle(0, ofGetHeight()/4, ofGetWidth()/2, ofGetHeight()/2));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') { bSwitch = !bSwitch; }
    if (key == 'h') { bViewInfo = !bViewInfo; }

    if (key == '1') { viewSensor.setSensorObject(0); }
    if (key == '2') { viewSensor.setSensorObject(1); }
    if (key == '3') { viewSensor.setSensorObject(2); }
    if (key == '4') { viewSensor.setSensorObject(3); }

    if (key == 'q') { viewSensor.setDrawMode(0); }
    if (key == 'w') { viewSensor.setDrawMode(1); }
    if (key == 'e') { viewSensor.setDrawMode(2); }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
