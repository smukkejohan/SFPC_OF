#pragma once

#include "ofMain.h"
#include "ofxScreenGrab.h"


class Frame : public ofFbo {
public:
    Frame() {
        allocate(ofGetScreenWidth(), ofGetScreenHeight());
        begin();
        ofBackground(0);
        end();
    }
};


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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxScreenGrab grabber;
    
    vector<ofPoint> NormCirclePts;
    vector<ofPoint> NormCircleCoords;
    
    ofFbo canvas;
    
    vector<Frame> frames;
    
    int maxFrames;
    int framerate;
    
    
    // Parameters
    float maxRadius;
    
    ofParameter<float> radius;
    ofParameter<float> speed;
    
    
    ofParameter<ofVec2f> anchor;
    
    ofParameter<bool> holdAnchor;
    ofParameter<bool> continousGrab;
    
    
    ofParameter<float> feather;
    
    ofParameter<bool> isPlaying;
    
    
    ofTexture tex;
    
    ofFbo frame;
    
    
    // blendmodes, hold R G B to only grab channels
    
    // GLUT's
    
    
    // Decay with time
    
    
    // Gravity mode
    
    
};
