//
//  ViewSensor.hpp
//  sensor_data_visualizer
//
//  Created by Almina on 2020/05/31.
//

#ifndef ViewSensor_hpp
#define ViewSensor_hpp

#include "ofMain.h"
#include "BasicView.hpp"

#include "ofxCsv.h"
#include "SensorObject.hpp"
#include "Sensor.hpp"

class ViewSensor : public BasicView {
    
    public:
        ViewSensor();
        void load();
        void update();
        void draw(ofRectangle r);
        void drawData(ofRectangle r);
        void drawGraph(ofRectangle r);
        void draw3d(ofRectangle r);

        void drawCircleOnSphere(float lat, float lon, float rad, float d);
        ofVec3f ang2coord(float lat, float lon, float rad);
        float coord2lat(float x, float y, float z);
        float coord2lon(float x, float y, float z);

        void setTargetData(int mode);
        void setSensorData(int mode);
        void setViewMode(int mode);
        void setDataLabel(string label);
        void setViewColor(ofColor col);

        Sensor sensor;
        float acc_x, acc_y, acc_z;
        float grav_x, grav_y, grav_z;
        float gyro_x, gyro_y, gyro_z;
        float att_x, att_y, att_z, att_w;

        float tar_x, tar_y, tar_z;
        vector<float> tar_x_buf, tar_y_buf, tar_z_buf;

        int frame;
        SensorObject sensorObject;
        int viewMode;
        int viewDataIndex;
        string dataLabel;
        ofColor col;
};

#endif /* ViewSensor_hpp */
