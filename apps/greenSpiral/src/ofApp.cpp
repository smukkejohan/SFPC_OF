#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    links.clear();
    
    links.reserve(NUM_LINKS);
    
    for(int i=0; i<NUM_LINKS; i++) {
        
        OrbitLink ol;
        
        ol.setPosition(30, 30, 30);
        ol.setOrientation(ofVec3f(0,0,0));
        
        links.push_back(ol);

        
        if(i>0){
            links[i].setParent(links[i-1]);
        }
    }
    
    
    links[0].setPosition(0, 0, -400);
    
    
    light.setPointLight();
    light.setAmbientColor(ofColor(200));
    light.setAttenuation(10);
    light.setParent(links[links.size()-1]);
    light.enable();
    
    cam.setupPerspective();
    cam.setParent(links[links.size()-1]);
    cam.setPosition(ofVec3f(0,0,500));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //cam.lookAt(links[0]);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(10,10,10);
    
    ofEnableAlphaBlending();
    ofEnableLighting();
    ofEnableDepthTest();
    
    cam.begin();
    
    
    for(int i=0; i<links.size(); i++) {
        
        //links[i].orbit(sin(ofGetElapsedTimef()), sin(ofGetElapsedTimef()), 10);
    
        links[i].roll( powf(sin(ofGetElapsedTimef()),2) );
        
        links[i].draw();
        
        if(links[i].getParent()){
            ofLine(links[i].getGlobalPosition(), links[i].getParent()->getGlobalPosition());
        }

        
    }
    
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
