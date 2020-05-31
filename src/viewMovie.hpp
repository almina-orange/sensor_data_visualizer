//
//  ViewMovie.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#ifndef ViewMovie_hpp
#define ViewMovie_hpp

#include "ofMain.h"

class ViewMovie {
    
    public:
        ViewMovie();
        void load();
        void load(string filepath);
        void update();
        void draw(ofRectangle r);

        ofVideoPlayer movie;
};

#endif /* ViewMovie_hpp */
