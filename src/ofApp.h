#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCsv.h"
#include "ofxSoundPlayerObject.h"
#include "FftObject.h"
#include "waveformDraw.h"
#include "SensorObject.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void csvLoad();
		void movieLoad();
		void audioLoad();
		void setSensorObject(int mode);

		void separatedWindow();
		void duplicatedWindow();
		void viewLabel(int x, int y, int w, int h);
		
		ofxCsv csv;
		ofVideoPlayer movie;

		ofSoundStream stream;
		ofxSoundOutput output;
		ofxSoundInput input;

		// these are all subclasses of ofSoundObject
		ofxSoundPlayerObject player;
		FftObject fft;
		waveformDraw wave;
		waveformDraw fullWave;

		SensorObject senObj;

		bool bSwitch, bViewInfo;
		int drawMode;
};
