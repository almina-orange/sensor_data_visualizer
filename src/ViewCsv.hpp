//
//  ViewCsv.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/06/06.
//

#ifndef ViewCsv_hpp
#define ViewCsv_hpp

#include "ofMain.h"
#include "ViewSensor.hpp"

class ViewCsv : public ViewSensor {
    
    public:
        void load();
        void load(string filepath);
        void update();
        void draw(ofRectangle r);

        string filepath;
        ofxCsv csv;
};

#endif /* ViewCsv_hpp */
