//
//  ViewAudio.cpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#include "ViewAudio.hpp"

//--------------------------------------------------------------
ViewAudio::ViewAudio(){

}

//--------------------------------------------------------------
void ViewAudio::load(){
    ofFileDialogResult result = ofSystemLoadDialog("Please select an audio file (.mp3, .wav, .aiff, .acc");
    if (result.bSuccess) { this->load(result.getPath()); }
}

//--------------------------------------------------------------
void ViewAudio::load(string filepath){
    player.load(filepath);

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
void ViewAudio::update(){

}

//--------------------------------------------------------------
void ViewAudio::draw(ofRectangle r){
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
