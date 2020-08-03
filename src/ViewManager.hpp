//
//  ViewManager.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/06.
//

#ifndef ViewManager_hpp
#define ViewManager_hpp

#include "ofMain.h"

#include "ViewMovie.hpp"
#include "ViewAudio.hpp"
#include "ViewLabel.hpp"
#include "ViewCsv.hpp"
#include "ViewOsc.hpp"

class ViewManager {
    
    public:
        ViewManager();
        void load();
        void update();
        void draw(ofRectangle r);

        void duplicatedLayout(ofRectangle r);
        void separatedLayout(ofRectangle r);
        void singleLayout(ofRectangle r);
        void zoomLayout(ofRectangle r);
        
        void setViewCenter(ofVec2f c);
        void switchViewLayout();
        void switchViewTarget();

        void switchViewMovieInput();
        void switchViewAudioInput();
        void switchViewSensorInput();
        void switchSensorViewMode();
        void switchSensorViewData();

        void switchViewMoviePlay();
        void switchViewAudioPlay();
        void switchViewSensorPlay();

        void clearView();

        bool onMouseViewMovie(int x, int y);
        bool onMouseViewAudio(int x, int y);
        bool onMouseViewSensor(int x, int y);
        bool onMouseViewLabel(int x, int y);

        ViewMovie viewMovie;
        ViewAudio viewAudio;
        ViewLabel viewLabel;
        ViewCsv viewCsv;
        ViewOsc viewOsc;

        ofRectangle regViewMovie;
        ofRectangle regViewAudio;
        ofRectangle regViewSensor;
        ofRectangle regViewLabel;

        int viewLayout;
        int viewTarget;
        int sensorViewMode;
        int sensorViewDataIndex;
        bool bViewCsv;
        ofVec2f viewCenter;

        const int LAYOUT_NUM = 4;
};

#endif /* ViewManager_hpp */
