#pragma once

#include "ofMain.h"
#include "ofxBiquadFilter.h"
#include "ofxSyphon.h"


#define NUM_LINKS 120

class OrbitLink : public ofNode {
public:
    
    void setup() {
        
        posHighPass.setType(OFX_BIQUAD_TYPE_HIGHPASS);
        posHighPass.setFc(0.025);
        
    };
    
    void customDraw() {
        ofFill();
        ofColor col;
        col = ofColor(255,255,255, 230);
        //col.setHueAngle(0.5);
        //ofSetColor(20, 255, 255, 230);
        //col.set(abs(posHighPass.value().x)*5.0,abs(posHighPass.value().y)*5.0,abs(posHighPass.value().z)*5.0, 200);
        
        col.setBrightness((abs(posHighPass.value().x)+abs(posHighPass.value().y)+abs(posHighPass.value().z))*10);
        
        col.setSaturation((abs(posHighPass.value().x)+abs(posHighPass.value().y)+abs(posHighPass.value().z))*10);
        
        ofSetColor(col);
        
        ofDrawBox(0, 0, 0, 10);
        ofNoFill();
        
        ofSetColor(255);
        //ofDrawBox(0, 0, 0, 12);
    };
    
    void update() {
        posHighPass.update(getGlobalPosition());
       // setOrientation(getOrientationEuler()*ofVec3f(0.1, 1, 1));
    };
    
    ofxBiquadFilter3f posHighPass;
    ofColor col;
    
};


class ofApp : public ofBaseApp{

	public:
    
    ofxSyphonServer syphon;
    
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
