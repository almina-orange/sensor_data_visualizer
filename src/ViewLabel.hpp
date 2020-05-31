//
//  ViewLabel.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#ifndef ViewLabel_hpp
#define ViewLabel_hpp

#include "ofMain.h"

class ViewLabel {
    
    public:
        ViewLabel();
        void load();
        void update();
        void draw(ofRectangle r);
};

#endif /* ViewLabel_hpp */
