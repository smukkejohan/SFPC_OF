#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    setWindowTransparent();
    ofSetFrameRate(25);
    
    grabwidth = 250;
    MSA::ofxCocoa::setCaptureExternalMouseEvents(true);
    screenGrabber.setup(grabwidth, grabwidth, true);
    ofRegisterMouseOutside(this);

    ofSetBackgroundAuto(false);
    
    lastWindowPos = windowPos;
}

//--------------------------------------------------------------

void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float travel = ofClamp(windowPos.distance(lastWindowPos), 0, 20);
    if(travel == 0) {
        alpha *= 0.8;
    } else {
        alpha += 0.01 + travel/200;
    }
    alpha = ofClamp(alpha, 0.1, 1);
    
    lastWindowPos = windowPos;
    
    
    int x = ofClamp(screenPos.x, 0, ofGetScreenWidth()-grabwidth/2);
    int y = ofClamp(screenPos.y, 0, ofGetScreenHeight()-grabwidth/2);
    screenGrabber.grabScreen(x-grabwidth/2, y-grabwidth/2);
    
    
    ofSetColor(255, 255, 255, 100);
    
    if(ofGetFrameNum() % 30 == 0) {
    if(ofRandom(1.0)<0.8) {
        rowCount = ofRandom(4,24);
    } else {	
        rowCount = ofRandom(24,220);
    }
    }
    
    if(ofGetFrameNum() % 30 == 15) {
        
        if(ofRandom(1.0)<0.8) {
            colCount = ofRandom(4,24);
        } else {
            colCount = ofRandom(24,220);
        }
    }
    
    
    if(ofGetFrameNum() % 30*10 == 0) {
        linealpha = ofRandom(20,255);
        
        float r = ofRandom(1.0);
        if(r >0.6) {
            linealpha = ofRandom(180,220);
        } else if (r>0.95) {
            linealpha = 255;
        } else {
            linealpha = ofRandom(20,150);
        }
    }
    
    
    if(ofGetFrameNum() % 30*5 == 0) {
        if(ofRandom(1.0)<0.1 ){
            issquare = true;
        } else {
            issquare = true;
        }
    }
    
    
    if(issquare) colCount = rowCount;
    
    int row = int(ofGetFrameNum()) % rowCount;
    int col = int(ofGetFrameNum()) % colCount;
    
        ofFbo fboRow;
        fboRow.allocate(ofGetScreenWidth(), ofGetScreenHeight()/rowCount);
        
        fboRow.begin();
        fboRow.end();
        
        ofSetColor(255, 255, 255, linealpha);
        fboRow.draw(0, row * (ofGetScreenHeight()/rowCount) );
    
    ofFbo fboCol;
    fboCol.allocate(ofGetScreenWidth()/colCount, 0);
    
    fboCol.begin();
    fboCol.end();
    
    ofSetColor(255, 255, 255, linealpha);
    fboCol.draw(col * ofGetScreenWidth()/colCount, 0);
    
    
    
    //ofTranslate(windowPos.x-grabwidth/2,windowPos.y-grabwidth/2);
    
    ofPushMatrix();
    
    ofTranslate(windowPos.x-grabwidth/2,windowPos.y-grabwidth/2);
    ofSetColor(255, 255, 255, 120*alpha);
    screenGrabber.draw(0,0);
    
    ofSetColor(255, 255, 255, 255);
    screenGrabber.getTextureReference().drawSubsection(grabwidth/4, grabwidth/4, grabwidth/2, grabwidth/2, grabwidth/2, grabwidth/2, grabwidth, grabwidth);
    
    ofPopMatrix();
    
    
    

    //ofBackground(255, 0, 0);
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

