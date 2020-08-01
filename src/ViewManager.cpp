//
//  ViewManager.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/06.
//

#include "ViewManager.hpp"

//--------------------------------------------------------------
ViewManager::ViewManager(){
    viewMovie.load("fingers.mov");
    viewAudio.load("/Users/almina/Downloads/of_v0.10.0_osx_release/apps/myApps/sensor_data_visualizer/bin/data/beat.wav");
    viewCsv.load("2020-0427-134121.csv");
    viewOsc.load();
    viewLabel.load();

    separatedLayout(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));

    viewLayout = 0;
    viewTarget = 0;
    sensorViewMode = 0;
    sensorViewDataIndex = 0;
    bViewCsv = true;
    viewCenter = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
}

//--------------------------------------------------------------
void ViewManager::load(){
    viewMovie.load();
    viewAudio.load();
    viewCsv.load();
    viewOsc.load();
    viewLabel.load();
}

//--------------------------------------------------------------
void ViewManager::update(){
    viewMovie.update();
    viewAudio.update();
    viewCsv.update();
    viewOsc.update();
    viewLabel.update();
}

//--------------------------------------------------------------
void ViewManager::draw(ofRectangle r){
    if (viewLayout == 0) { separatedLayout(r); }
    if (viewLayout == 1) { duplicatedLayout(r); }
    if (viewLayout == 2) { singleLayout(r); }
    if (viewLayout == 3) { zoomLayout(r); }

    viewMovie.draw(regViewMovie);
    viewAudio.draw(regViewAudio);
    if (bViewCsv) { viewCsv.draw(regViewSensor); }
    else          { viewOsc.draw(regViewSensor); }
    viewLabel.draw(regViewLabel);
}

//--------------------------------------------------------------
void ViewManager::duplicatedLayout(ofRectangle r){
    regViewMovie  = ofRectangle(r.x, r.y, r.width, r.height);
    regViewAudio  = ofRectangle(r.x, r.y, r.width, r.height);
    regViewSensor = ofRectangle(r.x, r.y, r.width, r.height);
    regViewLabel  = ofRectangle(r.x, r.y, r.width, r.height);
}

//--------------------------------------------------------------
void ViewManager::separatedLayout(ofRectangle r){
    // regViewMovie  = ofRectangle(r.x          , r.y           , r.width/2, r.height/2);
    // regViewAudio  = ofRectangle(r.x          , r.y+r.height/2, r.width/2, r.height/2);
    // regViewSensor = ofRectangle(r.x+r.width/2, r.y           , r.width/2, r.height/2);
    // regViewLabel  = ofRectangle(r.x+r.width/2, r.y+r.height/2, r.width/2, r.height/2);

    regViewMovie  = ofRectangle(r.x         , r.y         , viewCenter.x-r.x          , viewCenter.y-r.y           );
    regViewAudio  = ofRectangle(r.x         , viewCenter.y, viewCenter.x-r.x          , r.height-(viewCenter.y-r.y));
    regViewSensor = ofRectangle(viewCenter.x, r.y         , r.width-(viewCenter.x-r.x), viewCenter.y-r.y           );
    regViewLabel  = ofRectangle(viewCenter.x, viewCenter.y, r.width-(viewCenter.x-r.x), r.height-(viewCenter.y-r.y));
}

//--------------------------------------------------------------
void ViewManager::singleLayout(ofRectangle r){
    regViewMovie  = ofRectangle(r.x+r.width, r.y+r.height, r.width, r.height);
    regViewAudio  = ofRectangle(r.x+r.width, r.y+r.height, r.width, r.height);
    regViewSensor = ofRectangle(r.x+r.width, r.y+r.height, r.width, r.height);
    regViewLabel  = ofRectangle(r.x+r.width, r.y+r.height, r.width, r.height);

    ofRectangle mainR = ofRectangle(r.x, r.y, r.width, r.height);
    if (viewTarget == 0) { regViewMovie  = mainR; }
    if (viewTarget == 1) { regViewAudio  = mainR; }
    if (viewTarget == 2) { regViewSensor = mainR; }
    if (viewTarget == 3) { regViewLabel  = mainR; }
}

//--------------------------------------------------------------
void ViewManager::zoomLayout(ofRectangle r){
    ofRectangle mainR = ofRectangle(r.x            , r.y             , r.width  , r.height/3*2);
    ofRectangle colR1 = ofRectangle(r.x+r.width/3*0, r.y+r.height/3*2, r.width/3, r.height/3  );
    ofRectangle colR2 = ofRectangle(r.x+r.width/3*1, r.y+r.height/3*2, r.width/3, r.height/3  );
    ofRectangle colR3 = ofRectangle(r.x+r.width/3*2, r.y+r.height/3*2, r.width/3, r.height/3  );
    if (viewTarget == 0) { regViewMovie = mainR;  regViewAudio = colR1;  regViewSensor = colR2;  regViewLabel = colR3; }
    if (viewTarget == 1) { regViewMovie = colR1;  regViewAudio = mainR;  regViewSensor = colR2;  regViewLabel = colR3; }
    if (viewTarget == 2) { regViewMovie = colR1;  regViewAudio = colR2;  regViewSensor = mainR;  regViewLabel = colR3; }
    if (viewTarget == 3) { regViewMovie = colR1;  regViewAudio = colR2;  regViewSensor = colR3;  regViewLabel = mainR; }
}

//--------------------------------------------------------------
void ViewManager::setViewCenter(ofVec2f c){
    viewCenter = c;
}

//--------------------------------------------------------------
void ViewManager::switchViewMovieInput(){
    viewMovie.switchInput();
}

//--------------------------------------------------------------
void ViewManager::switchViewAudioInput(){
    viewAudio.switchInput();
}

//--------------------------------------------------------------
void ViewManager::switchViewSensorInput(){
    bViewCsv = !(bViewCsv);
}

//--------------------------------------------------------------
void ViewManager::switchViewLayout(){
    viewLayout = (viewLayout + 1) % LAYOUT_NUM;
}

//--------------------------------------------------------------
void ViewManager::switchViewTarget(){
    viewTarget = (viewTarget + 1) % LAYOUT_NUM;
}

//--------------------------------------------------------------
void ViewManager::switchSensorViewMode(){
    sensorViewMode = (sensorViewMode + 1) % 3;
    viewCsv.setViewMode(sensorViewMode);
    viewOsc.setViewMode(sensorViewMode);
}

//--------------------------------------------------------------
void ViewManager::switchSensorViewData(){
    sensorViewDataIndex = (sensorViewDataIndex + 1) % 4;
    viewCsv.setSensorData(sensorViewDataIndex);
    viewOsc.setSensorData(sensorViewDataIndex);
}

//--------------------------------------------------------------
bool ViewManager::onMouseViewMovie(int x, int y){
    return regViewMovie.inside(x, y);
}

//--------------------------------------------------------------
bool ViewManager::onMouseViewAudio(int x, int y){
    return regViewAudio.inside(x, y);
}

//--------------------------------------------------------------
bool ViewManager::onMouseViewSensor(int x, int y){
    return regViewSensor.inside(x, y);
}

//--------------------------------------------------------------
bool ViewManager::onMouseViewLabel(int x, int y){
    return regViewLabel.inside(x, y);
}