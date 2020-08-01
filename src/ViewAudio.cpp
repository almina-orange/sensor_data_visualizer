//
//  ViewAudio.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#include "ViewAudio.hpp"

//--------------------------------------------------------------
ViewAudio::ViewAudio(){
    bViewAudioFile = true;
}

//--------------------------------------------------------------
void ViewAudio::load(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select an audio file (.mp3, .wav, .aiff, .acc");
    if (result.bSuccess) { this->load(result.getPath()); }
}

//--------------------------------------------------------------
void ViewAudio::load(string filepath){
    this->filepath = filepath;
    player.load(filepath);

    int bufferSize = 512;
    ofSoundStreamSettings settings;
    settings.numInputChannels = 2;
    settings.numOutputChannels = 2;
    // settings.sampleRate = player.getSoundFile().getSampleRate();
    settings.sampleRate = 44100;
    settings.bufferSize = bufferSize;
    settings.numBuffers = 4;

    stream.setup(settings);
    stream.setInput(input);
    stream.setOutput(output);

    fft.setup(bufferSize);

    fullWave.makeMeshFromBuffer(player.getSoundFile().getBuffer());

    player.connectTo(wave).connectTo(fft).connectTo(output);
    player.setLoop(true);
    player.play();
}

//--------------------------------------------------------------
void ViewAudio::draw(ofRectangle r){
    viewArea = r;

    ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);
    ofRectangle rs = r;
    rs.scaleFromCenter(0.85);
    ofFill();  ofSetColor(0, 0, 0, 100);  ofDrawRectangle(rs);
    ofNoFill();  ofSetColor(255, 0, 0);   ofDrawRectangle(rs);

    if (bViewAudioFile) {
        fullWave.draw(ofRectangle(rs.x, rs.y+rs.height/3*0, rs.width, rs.height/3));
        wave.draw(    ofRectangle(rs.x, rs.y+rs.height/3*1, rs.width, rs.height/3));
        fft.draw(     ofRectangle(rs.x, rs.y+rs.height/3*2, rs.width, rs.height/3));
        float head = ofMap(player.getPosition(), 0, 1, rs.x, rs.x+rs.width);
        ofDrawLine(head, rs.y, head, rs.y+rs.height/3);
        ofNoFill();  ofSetColor(255);  ofDrawRectangle(r);

        ofDrawBitmapStringHighlight(filepath, rs.x + 20, rs.y + 20, ofColor(0, 150));
    } else {
        wave.draw(ofRectangle(rs.x, rs.y+rs.height/2*0, rs.width, rs.height/2));
        fft.draw( ofRectangle(rs.x, rs.y+rs.height/2*1, rs.width, rs.height/2));
    }
}

//--------------------------------------------------------------
void ViewAudio::switchInput(){
    bViewAudioFile = !(bViewAudioFile);
    if (bViewAudioFile) { player.connectTo(wave); }
    else { input.connectTo(wave); }
}
