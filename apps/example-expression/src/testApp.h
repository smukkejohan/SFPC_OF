#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"


class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
    
    ofSerial serial;
    ofImage matrix1;
    ofImage matrix2;
    
    ofFbo eye;
    ofPixels pix;
    
    ofImage eyeOpen;
    ofImage eyeClosed;
    
};
