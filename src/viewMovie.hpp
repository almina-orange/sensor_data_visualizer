//
//  ViewMovie.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#ifndef ViewMovie_hpp
#define ViewMovie_hpp

#include "ofMain.h"
#include "BasicView.hpp"

class ViewMovie : public BasicView {
    
    public:
        ViewMovie();
        void load();
        void load(string filepath);
        void update();
        void draw(ofRectangle r);
        void switchInput();
        void switchPlaying();
        void clear();

        string filepath;
        ofVideoPlayer movie;
        ofVideoGrabber camera;

        bool bViewMovieFile;

        int frame;
};

#endif /* ViewMovie_hpp */
