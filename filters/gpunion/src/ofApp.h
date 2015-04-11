#pragma once
#include "ofMain.h"
#include "screenGrab.h"
#include "ofxCocoa.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
    
        void mouseMovedOutside(ofMouseEventArgs & arg);
        void mouseDraggedOutside(ofMouseEventArgs & arg);
        void mousePressedOutside(ofMouseEventArgs & arg);
        void mouseReleasedOutside(ofMouseEventArgs & arg);
    
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofPoint easedMouse;
    
        ScreenGrab screenGrabber;
        //MSA::ofxCocoa::Events cocoEvents;
        //cocoaEvents cevents;
    
        float mX;
        float mY;
        int grabwidth;
    
        ofVec2f screenPos;
        ofVec2f windowPos;
    
    int rowCount=4;
    int colCount=4;
    
    float alpha;
    float speed=4;
    
    ofVec2f lastWindowPos;
    
        bool hasFocus = true;
    
     ofPixels pix;
    ofTexture roi;
    
    bool issquare = false;
    
    ofColor targetColor;
    float threshold;
    float linealpha = 255;
    //ofxCv::TrackingColorMode trackingColorMode;
    //ofColor targetColor;
    
};

