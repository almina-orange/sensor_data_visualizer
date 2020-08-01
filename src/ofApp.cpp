#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofApp");
    
    ofSetFrameRate(50);
    ofBackground(0);
    ofSetCircleResolution(32);
    // ofEnableDepthTest();
    // ofEnableSmoothing();

    bViewInfo = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    viewManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSeedRandom(0);

    viewManager.draw(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));

    ofDrawBitmapStringHighlight("[h]: view info", 20, 20);
    if (bViewInfo) {
        ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate()), 20, 40);
        ofDrawBitmapStringHighlight("[spqce]: switch view layout", 20, 60);
        ofDrawBitmapStringHighlight("[a]: switch sensor data (att/gyro/grav/acc)", 20, 80);
        ofDrawBitmapStringHighlight("[s]: switch sensor view mode (3d/graph/num)", 20, 100);
        ofDrawBitmapStringHighlight("[f]: switch target view (mov/aud/sen/lab)", 20, 120);
        ofDrawBitmapStringHighlight("onMouse + [d]: switch input (sim/real)", 20, 140);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') { viewManager.switchViewLayout(); }
    if (key == 'f') { viewManager.switchViewTarget(); }
    if (key == 'a') { viewManager.switchSensorViewMode(); }
    if (key == 's') { viewManager.switchSensorViewData(); }

    if (key == 'd') {
        if (viewManager.onMouseViewMovie(mouseX, mouseY)) {
            viewManager.switchViewMovieInput();
        }
        if (viewManager.onMouseViewAudio(mouseX, mouseY)) {
            viewManager.switchViewAudioInput();
        }
        if (viewManager.onMouseViewSensor(mouseX, mouseY)) {
            viewManager.switchViewSensorInput();
        }
    }

    if (key == 'h') { bViewInfo = !bViewInfo; }
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
    viewManager.setViewCenter(ofVec2f(x, y));
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
