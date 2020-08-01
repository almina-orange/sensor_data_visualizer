//
//  BasicView.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/06.
//

#ifndef BasicView_hpp
#define BasicView_hpp

#include "ofMain.h"

class BasicView {
    
    public:
        BasicView();
        void load();
        void update();
        void draw(ofRectangle r);
        bool onMouse(int x, int y);

        float frame;
        ofRectangle viewArea;
};

#endif /* BasicView_hpp */
