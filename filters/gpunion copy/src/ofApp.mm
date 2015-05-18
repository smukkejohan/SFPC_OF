#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    //setWindowTransparent();
    
    ofSetFrameRate(30);
    
    //grabwidth = 250;
    MSA::ofxCocoa::setCaptureExternalMouseEvents(true);
    screenGrabber.setup(10, 10, true);
    ofRegisterMouseOutside(this);

    ofSetBackgroundAuto(false);
    lastWindowPos = windowPos;
    
    
    sender.setup("Rumba.local",7654);
}

//--------------------------------------------------------------

void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    lastWindowPos = windowPos;
    
    screenGrabber.grabScreen(screenPos.x-5, screenPos.y-5);
    screenGrabber.getTextureReference().readToPixels(pix);
    
    
    col = pix.getColor(5, 5);
    
    ofxOscMessage m;
    m.setAddress("/m/col");
    m.addIntArg(col.r);
    m.addIntArg(col.g);
    m.addIntArg(col.b);
    sender.sendMessage(m);
    
    
    ofBackground(col);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //cout<<key<<endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}


void ofApp::mousePress(int state) {
    
    ofxOscMessage m;
    m.setAddress("/m/btn");
    m.addIntArg(state);
    sender.sendMessage(m);
}

void ofApp::mouseMove() {
    
    ofxOscMessage m;
    m.setAddress("/m/pos");
    // send normalized
    m.addFloatArg(screenPos.x/ofGetScreenWidth());
    m.addFloatArg(screenPos.y/ofGetScreenHeight());
    sender.sendMessage(m);
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    hasFocus = true;
    
    windowPos.x = x;
    windowPos.y = y;
    
    screenPos.x = x+ofGetWindowPositionX();
    int dif = ofGetScreenHeight()-ofGetWindowHeight();
    screenPos.y = y+dif-ofGetWindowPositionY();
    
    mouseMove();
    
}

//--------------------------------------------------------------
void ofApp::mouseMovedOutside(ofMouseEventArgs & arg){
    
    int dif = ofGetScreenHeight()-ofGetWindowHeight();
    
    screenPos.x = arg.x;
    screenPos.y = arg.y;
    
    windowPos.x = arg.x-ofGetWindowPositionX();
    windowPos.y = arg.y-dif+ofGetWindowPositionY();
    
    mouseMove();
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mousePress(0);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mousePress(1);
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
    mousePress(0);
}

//--------------------------------------------------------------
void ofApp::mouseReleasedOutside(ofMouseEventArgs & arg){
    mousePress(1);
}

