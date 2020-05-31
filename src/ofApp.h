#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCsv.h"

#include "SensorObject.hpp"
#include "ViewMovie.hpp"
#include "ViewAudio.hpp"
#include "ViewSensor.hpp"
#include "ViewLabel.hpp"

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

		void separatedWindow();
		void duplicatedWindow();

		ViewMovie viewMovie;
		ViewAudio viewAudio;
		ViewSensor viewSensor;
		ViewLabel viewLabel;

		bool bSwitch, bViewInfo;
};
