//
//  ViewAudio.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#ifndef ViewAudio_hpp
#define ViewAudio_hpp

#include "ofMain.h"
#include "BasicView.hpp"

#include "ofxSoundPlayerObject.h"
#include "FftObject.h"
#include "waveformDraw.h"

class ViewAudio : public BasicView {
    
    public:
        ViewAudio();
        void load();
        void load(string filepath);
        void draw(ofRectangle r);
        void switchInput();
        void switchPlaying();
        void clear();

        string filepath;

        ofSoundStream stream;
        ofxSoundOutput output;
        ofxSoundInput input;

        // these are all subclasses of ofSoundObject
        ofxSoundPlayerObject player;
        FftObject fft;
        waveformDraw wave;
        waveformDraw fullWave;

        bool bViewAudioFile;
};

#endif /* ViewAudio_hpp */
