#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    setWindowTransparent();
    
    
    //NSWindow
    
    
    MSA::ofxCocoa::setCaptureExternalMouseEvents(true);
    //setCaptureExternalMouseEvents(true);
    
    ofBackground(0);
    
    screenGrabber.setup(200, 200, true);
    //cocoaEvents
    
    //ofAddListener(cocoaEvents.mouseMovedOutsideEvent,this,&ofApp::mouseMovedOutside);

    //MSA::ofxCocoa::
    ofRegisterMouseOutside(this);
    //MSA::ofxCocoa::Event::ofRegisterMouseOutside();
    //ofRegisterMouseOutside(&ofApp);

    //ofRegisterMouseOutside(cocoEvents);
    //ofRegisterMouseEvents(&ofApp);
}

//--------------------------------------------------------------

void ofApp::update(){
        
    //easedMouse = easedMouse * .9 + ofPoint(mX, mY) * .1;
    
    int x = mX - ofGetWindowPositionX() + 200;
    int y = mY - ofGetWindowPositionY() + ofGetHeight();
    
    screenGrabber.grabScreen(max(0,x), max(0,y));


}

//--------------------------------------------------------------
void ofApp::draw(){
    /*ofSetColor(ofClamp( easedMouse.distance(ofPoint(mX, mY)), 0, 255));
    ofCircle(easedMouse, 100);
    ofSetColor(255);
    ofRect(mX - 50, mY - 50, 100, 100);
    */
    ofRectMode(OF_RECTMODE_CENTER);
    screenGrabber.draw(mX,mY);
    
    
    cout<<mX<<" "<<mY<<endl;
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
    //cout<<x<<y<<endl;
    
    mX = x-ofGetWindowPositionX();
    mY = y-ofGetWindowPositionY();
    
    //cout<<x<<" "<<y<<endl;
}

//--------------------------------------------------------------
void ofApp::mouseMovedOutside(ofMouseEventArgs & arg){
    mX = arg.x-ofGetWindowPositionX() - ofGetWindowPositionX();
    mY = arg.y-ofGetWindowPositionY() - ofGetHeight()+ofGetWindowPositionY();
    
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

