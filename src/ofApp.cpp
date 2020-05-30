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

    // ofVec3f *att = new ofVec3f[csv.getNumRows()];
    // for (int i = 0; i < csv.getNumRows(); i++) {
    //     ofxCsvRow row = csv[i];
    //     att[i] = ofVec3f(row.getFloat( 1), row.getFloat( 2), row.getFloat( 3));
    // }
    // senObj.setup(att, csv.getNumRows(), ofFloatColor(0.0, 0.5, 1.0));

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
void ofApp::separatedWindow(){
    ofSetColor(ofFloatColor(0.3, 0.3, 0.3));
    movie.draw(0, 0, ofGetWidth() / 2, ofGetHeight() / 2);

    fullWave.draw(ofRectangle(0, ofGetHeight() / 6 * 3, ofGetWidth() / 2, ofGetHeight() / 6));
    wave.draw(ofRectangle(0, ofGetHeight() / 6 * 4, ofGetWidth() / 2, ofGetHeight() / 6));
    fft.draw(ofRectangle(0, ofGetHeight() / 6 * 5, ofGetWidth() / 2, ofGetHeight() / 6));
    float head = ofMap(player.getPosition(), 0, 1, 0, ofGetWidth() / 2);
    ofDrawLine(head, ofGetHeight() / 6 * 3, head, ofGetHeight() / 6 * 4);

    // player.drawDebug(0, ofGetHeight() / 2);

    viewLabel(ofGetWidth() / 2, ofGetHeight() / 2, ofGetWidth() / 2, ofGetHeight() / 2);

    if (drawMode == 0) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 4 * 3, ofGetHeight() / 4 * 1);
        ofRotateY(ofGetFrameNum() / 4);
        ofScale(0.5);
        senObj.draw3d();
        ofPopMatrix();
    } else if (drawMode == 1) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 4 * 1);
        ofScale(0.5);
        senObj.drawGraph();
        ofPopMatrix();
    } else if (drawMode == 2) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 4 * 1);
        senObj.drawData();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::duplicatedWindow(){
    ofSetColor(ofFloatColor(0.3, 0.3, 0.3));
    movie.draw(0, 0, ofGetWidth(), ofGetHeight());

    fullWave.draw(ofRectangle(0, ofGetHeight() / 3 * 0, ofGetWidth(), ofGetHeight() / 3));
    wave.draw(ofRectangle(0, ofGetHeight() / 3 * 1, ofGetWidth(), ofGetHeight() / 3));
    fft.draw(ofRectangle(0, ofGetHeight() / 3 * 2, ofGetWidth(), ofGetHeight() / 3));
    float head = ofMap(player.getPosition(), 0, 1, 0, ofGetWidth());
    ofDrawLine(head, ofGetHeight() / 3 * 0, head, ofGetHeight() / 3 * 1);

    // player.drawDebug(0, 0);

    viewLabel(0, ofGetHeight() / 4, ofGetWidth() / 2, ofGetHeight() / 2);

    if (drawMode == 0) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 4 * 3, ofGetHeight() / 4 * 2);
        ofRotateY(ofGetFrameNum() / 4);
        ofScale(0.5);
        senObj.draw3d();
        ofPopMatrix();
    } else if (drawMode == 1) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        ofScale(0.5);
        senObj.drawGraph();
        ofPopMatrix();
    } else if (drawMode == 2) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        senObj.drawData();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::viewLabel(int x, int y, int w, int h){
    // example bar graph
    ofFill();
    for (int i = 0; i < 8; i++) {
        ofDrawRectangle(
            x,
            ofMap(i, 0, 8, y, y+h),
            w - ofRandom(w),
            h / 8 * 0.5
        );
    }
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
