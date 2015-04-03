#include "ofApp.h"


using namespace ofxCv;
using namespace cv;


//--------------------------------------------------------------
void ofApp::setup(){
    setWindowTransparent();
    
    threshold = 20;
    
    grabwidth = 350;
    //NSWindow
    
    MSA::ofxCocoa::setCaptureExternalMouseEvents(true);
    //setCaptureExternalMouseEvents(true);
    
    ofBackground(0);
    
    screenGrabber.setup(grabwidth, grabwidth, true);
    
    //cocoaEvents
    ofAddListener(cocoaEvents.mouseMovedOutsideEvent,this,&ofApp::mouseMovedOutside);
    //MSA::ofxCocoa::
    ofRegisterMouseOutside(this);
    //MSA::ofxCocoa::Event::ofRegisterMouseOutside();
    //ofRegisterMouseOutside(&ofApp);

    //ofRegisterMouseOutside(cocoEvents);
    //ofRegisterMouseEvents(&ofApp);

    pix.allocate(grabwidth*2, grabwidth*2, OF_IMAGE_COLOR_ALPHA);
    
    
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(150);
    
}

//--------------------------------------------------------------

void ofApp::update(){
    //easedMouse = easedMouse * .9 + ofPoint(mX, mY) * .1;
    // todo check bounds
}

//--------------------------------------------------------------
void ofApp::draw(){
    /*ofSetColor(ofClamp( easedMouse.distance(ofPoint(mX, mY)), 0, 255));
    ofCircle(easedMouse, 100);
    ofSetColor(255);
    ofRect(mX - 50, mY - 50, 100, 100);
    */
    
    int x = ofClamp(screenPos.x, 0, ofGetScreenWidth()-grabwidth/2);
    int y = ofClamp(screenPos.y, 0, ofGetScreenHeight()-grabwidth/2);
    screenGrabber.grabScreen(x-grabwidth/2, y-grabwidth/2);
    
    screenGrabber.getTextureReference().readToPixels(pix);
    
    
    threshold = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    contourFinder.setThreshold(threshold);
    contourFinder.findContours(pix);
    
    
    
    ofRectMode(OF_RECTMODE_CORNER);
    ofTranslate(windowPos.x-grabwidth/2,windowPos.y-grabwidth/2);
    screenGrabber.draw(0,0);
    
    
    ofPushMatrix();
    
    ofScale(0.5, 0.5);
    contourFinder.draw();

    
    ofPopMatrix();
    
    //cout<<mX<<" "<<mY<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    hasFocus = true;
    
    windowPos.x = x;
    windowPos.y = y;
    
    screenPos.x = x+ofGetWindowPositionX();
    
    int dif = ofGetScreenHeight()-ofGetWindowHeight();
    
    screenPos.y = y+dif-ofGetWindowPositionY();
    
}

//--------------------------------------------------------------
void ofApp::mouseMovedOutside(ofMouseEventArgs & arg){
    
    int dif = ofGetScreenHeight()-ofGetWindowHeight();
    
    screenPos.x = arg.x;
    screenPos.y = arg.y;
    
    windowPos.x = arg.x-ofGetWindowPositionX();
    windowPos.y = arg.y-dif+ofGetWindowPositionY();
    
    
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::mouseDraggedOutside(ofMouseEventArgs & arg){
    
}

//--------------------------------------------------------------
void ofApp::mousePressedOutside(ofMouseEventArgs & arg){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleasedOutside(ofMouseEventArgs & arg){
    
}

