#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(50);
    ofBackground(0);
    ofSetCircleResolution(32);
    // ofEnableDepthTest();
    // ofEnableSmoothing();

    ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);

    csvLoad();
    movieLoad();
    audioLoad();

    setSensorObject(0);

    bSwitch = true;
    bViewInfo = false;
    drawMode = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
    senObj.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSeedRandom(0);

    if (bSwitch) { duplicatedWindow(); }
    else { separatedWindow(); }

    ofDrawBitmapStringHighlight("[h]: view info", 20, 20);
    if (bViewInfo) {
        ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate()), 20, 40);
        ofDrawBitmapStringHighlight("[spqce]: switch window mode (dup/sep)", 20, 60);
        ofDrawBitmapStringHighlight("[1..4]: switch sensor data (att/gyro/grav/acc)", 20, 80);
        ofDrawBitmapStringHighlight("[q/w/e]: switch sensor data style", 20, 100);
    }
}

// //--------------------------------------------------------------
// void ofApp::exampleView(ofRectangle r){
//     ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
//     ofRectangle rs = r;
//     rs.scaleFromCenter(0.85);
//     ofNoFill();  ofSetColor(255, 0, 0);  ofDrawRectangle(rs);
    
//     ofMesh m;
//     m.clear();  m.setMode(OF_PRIMITIVE_LINE_STRIP);
//     for (int i = 0; i < 100; i++) {
//         float x = ofMap(i, 0, 100-1, rs.x, rs.x+rs.width);
//         float y = ofMap(ofRandom(100), 0, 100-1, rs.y, rs.y+rs.height);
//         m.addVertex(ofVec3f(x, y));
//         m.addColor(ofColor::blueViolet);
//     }
//     m.draw();
// }

//--------------------------------------------------------------
void ofApp::csvLoad(){
    // read csv-file
    ofFileDialogResult result = ofSystemLoadDialog("Please select an audio file (.mp3, .wav, .aiff, .aac");
    if (result.bSuccess) {
        csv.load(result.getPath());
        csv.removeRow(0);  // remove header
    }
    // else {
    //     csv.load("2020-0427-134121.csv");
    //     csv.removeRow(0);  // remove header
    // }
    // // output full data for log
    // for (int i = 0; i < csv.getNumRows(); i++) {
    //     for (int j = 0; j < csv.getNumCols(); j++) {
    //         cout << csv[i][j] << ", ";
    //     }
    //     cout << endl;
    // }
}

//--------------------------------------------------------------
void ofApp::movieLoad(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select an movie file (.mov, .mp4");
    if (result.bSuccess) {
        movie.load(result.getPath());
        movie.setLoopState(OF_LOOP_NORMAL);
        movie.play();
    }
    // else {
    //     movie.load("fingers.mov");
    //     movie.setLoopState(OF_LOOP_NORMAL);
    //     movie.play();
    // }
}

//--------------------------------------------------------------
void ofApp::audioLoad(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select an audio file (.mp3, .wav, .aiff, .acc");
    if (result.bSuccess) { player.load(result.getPath()); }
    // else { player.load("/Users/almina/Downloads/of_v0.10.0_osx_release/apps/myApps/sensor_data_visualizer/bin/data/beat.wav"); }

    int bufferSize = 512;
    ofSoundStreamSettings settings;
    settings.numInputChannels = 0;
    settings.numOutputChannels = 2;
    settings.sampleRate = player.getSoundFile().getSampleRate();
    settings.bufferSize = bufferSize;
    settings.numBuffers = 4;

    stream.setup(settings);
    stream.setOutput(output);
    // stream.setInput(input);

    fft.setup(bufferSize);
    fullWave.makeMeshFromBuffer(player.getSoundFile().getBuffer());

    player.connectTo(wave).connectTo(fft).connectTo(output);
    player.setLoop(true);
    player.play();
}

//--------------------------------------------------------------
void ofApp::setSensorObject(int mode){
    ofFloatColor pal[4];
    pal[0] = ofFloatColor(0.0, 0.5, 1.0);
    pal[1] = ofFloatColor(1.0, 0.0, 0.5);
    pal[2] = ofFloatColor(1.0, 0.5, 0.0);
    pal[3] = ofFloatColor(0.5, 0.0, 1.0);

    int xi = mode * 3 + 1;
    int yi = mode * 3 + 2;
    int zi = mode * 3 + 3;
    ofVec3f *data = new ofVec3f[csv.getNumRows()];
    for (int i = 0; i < csv.getNumRows(); i++) {
        ofxCsvRow row = csv[i];
        data[i] = ofVec3f(row.getFloat(xi), row.getFloat(yi), row.getFloat(zi));
    }
    senObj.setup(data, csv.getNumRows(), pal[mode]);
}

//--------------------------------------------------------------
void ofApp::viewMovie(ofRectangle r){
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    ofSetColor(255);
    movie.draw(rs.x, rs.y, rs.width, rs.height);
}

//--------------------------------------------------------------
void ofApp::viewAudio(ofRectangle r){
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    fullWave.draw(ofRectangle(rs.x, rs.y+rs.height/3*0, rs.width, rs.height/3));
    wave.draw(    ofRectangle(rs.x, rs.y+rs.height/3*1, rs.width, rs.height/3));
    fft.draw(     ofRectangle(rs.x, rs.y+rs.height/3*2, rs.width, rs.height/3));
    float head = ofMap(player.getPosition(), 0, 1, rs.x, rs.x+rs.width);
    ofDrawLine(head, rs.y, head, rs.y+rs.height/3);
}

//--------------------------------------------------------------
void ofApp::viewSensor(ofRectangle r){
    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    if (drawMode == 0) { senObj.draw3d(rs); }
    else if (drawMode == 1) { senObj.drawGraph(rs); }
    else if (drawMode == 2) { senObj.drawData(rs); }
}

//--------------------------------------------------------------
void ofApp::viewLabel(ofRectangle r){
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

//--------------------------------------------------------------
void ofApp::separatedWindow(){
    viewMovie(ofRectangle(0, 0, ofGetWidth()/2, ofGetHeight()/2));
    viewAudio(ofRectangle(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2));
    viewSensor(ofRectangle(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2));
    viewLabel(ofRectangle(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2));
}

//--------------------------------------------------------------
void ofApp::duplicatedWindow(){
    viewMovie(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    viewAudio(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    viewSensor(ofRectangle(ofGetWidth()/2, ofGetHeight()/4, ofGetWidth()/2, ofGetHeight()/2));
    viewLabel(ofRectangle(0, ofGetHeight()/4, ofGetWidth()/2, ofGetHeight()/2));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') { bSwitch = !bSwitch; }
    if (key == 'h') { bViewInfo = !bViewInfo; }

    if (key == '1') { setSensorObject(0); }
    if (key == '2') { setSensorObject(1); }
    if (key == '3') { setSensorObject(2); }
    if (key == '4') { setSensorObject(3); }

    if (key == 'q') { drawMode = 0; }
    if (key == 'w') { drawMode = 1; }
    if (key == 'e') { drawMode = 2; }
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
