#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    setWindowTransparent();
    
    ofSetFrameRate(25);
    
    //grabwidth = 250;
    //NSWindow
    
    MSA::ofxCocoa::setCaptureExternalMouseEvents(true);
    MSA::ofxCocoa::setTransparent(true);
    //setCaptureExternalMouseEvents(true);
    
    //ofBackground(0);
    
    screenGrabber.setup(ofGetScreenWidth(), ofGetScreenHeight(), true);
    
    //cocoaEvents
    ofAddListener(cocoaEvents.mouseMovedOutsideEvent,this,&ofApp::mouseMovedOutside);
    //MSA::ofxCocoa::
    ofRegisterMouseOutside(this);
    //MSA::ofxCocoa::Event::ofRegisterMouseOutside();
    //ofRegisterMouseOutside(&ofApp);

    //ofRegisterMouseOutside(cocoEvents);
    //ofRegisterMouseEvents(&ofApp);

    //pix.allocate(grabwidth, grabwidth, OF_IMAGE_COLOR_ALPHA);
    
    //contourFinder.setMinAreaRadius(5);
    //contourFinder.setMaxAreaRadius(200);
    
    //contourFinder.setUseTargetColor(false);
    ofSetBackgroundAuto(false);
    
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
    
    ofSetColor(255, 255, 255, 100);
    
    int x = ofClamp(screenPos.x, 0, ofGetScreenWidth()-grabwidth/2);
    int y = ofClamp(screenPos.y, 0, ofGetScreenHeight()-grabwidth/2);
    screenGrabber.grabScreen(0,0);
    
    ofFbo fbo;
    
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo.begin();
    ofRectMode(OF_RECTMODE_CORNER);
    //ofTranslate(windowPos.x-grabwidth/2,windowPos.y-grabwidth/2);
    
    int dif = ofGetScreenHeight()-ofGetWindowHeight();
    //screenGrabber.draw(0-ofGetWindowPositionX(),-dif+ofGetWindowPositionY());
    fbo.end();
    
    //fbo.draw(0, 0);
    
    screenGrabber.draw(0, 0);
    
    //ofSetColor(targetColor);
    //ofRect(-40+grabwidth/2,-40+grabwidth/2,40,40);
    
    
    //cout<<mX<<" "<<mY<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //cout<<key<<endl;
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

