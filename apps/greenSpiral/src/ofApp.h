#pragma once

#include "ofMain.h"

#define NUM_LINKS 80

class OrbitLink : public ofNode {
public:
    void customDraw() {
        
        ofFill();
        ofSetColor(200, 255, 200, 180);
        ofDrawBox(0, 0, 0, 8);
        ofNoFill();
        ofSetColor(255);
        ofDrawBox(0, 0, 0, 10);
        
    };
    
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
    
    
    vector<OrbitLink> links;
    
    ofCamera cam;

    ofLight light;
    
    
};
