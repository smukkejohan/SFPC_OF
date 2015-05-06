#pragma once

#include "ofMain.h"
#include "ofxSlitScan.h"
#include "ofxUI.h"
#include "ofxSyphon.h"


class ofApp : public ofBaseApp{
  public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxSlitScan slitScan;
    ofVideoGrabber grabber;
    
    ofFbo mapFbo;
    ofFbo inputFbo;
    
    ofPixels mapPixels;
    ofImage gradient;
    
    ofPixels moviePixels;
    
    unsigned char* inPixels;
    
    ofxUICanvas * gui;
    
    float delay = 10;
    float width = 0;
    ofImage distortionMap;
    
    ofxSyphonServer syphonOut;
    ofxSyphonClient syphonMovieIn;
    ofxSyphonClient syphonDisplacementMapIn;
    
    ofxSyphonServerDirectory directory;
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    int dirIdMap;
    int dirIdMovie;
    
    //ofVideoPlayer player;
    ofImage movieImage;
    
};
