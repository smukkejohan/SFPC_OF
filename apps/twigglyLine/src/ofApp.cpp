#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
    
    links.clear();
    
    links.reserve(NUM_LINKS);
    
    for(int i=0; i<NUM_LINKS; i++) {
        
        OrbitLink ol;
        
        ol.setPosition(28, 0, 0);
        
        // squicgly line
        ol.setOrientation(ofVec3f(ofRandom(360),0,ofRandom(360)));
        //ol.setOrientation(ofVec3f(8,0,8));
        
        
        links.push_back(ol);
        
        
        links[i].setup();
        
        if(i>0){
            links[i].setParent(links[i-1]);
        }
    }
    
    
    links[0].setPosition(0, 0, -400);
    
    
    light.setPointLight();
    light.setAmbientColor(ofColor(255));
    light.setAttenuation(400);
    light.setDiffuseColor(255);
    //light.setup();
    //light.setParent(links[links.size()-1]);
    light.enable();
    
    cam.setupPerspective();
    //cam.setParent(links[links.size()-1]);
    cam.setPosition(links[links.size()-1].getPosition());
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //cam.lookAt(links[links.size()/2]);
        for(int i=0; i<links.size(); i++) {
        
            //links[i].orbit(sin(ofGetElapsedTimef()), sin(ofGetElapsedTimef()), 10);
            
            //links[i].roll( powf(sin(ofGetElapsedTimef()),i) );
            //links[i].rotate(powf(sin(ofGetElapsedTimef()),i), ofVec3f(0,0,1));
            
            
            // springy thing
            links[i].rotate(cos(ofGetFrameNum()/400.0), ofVec3f(0,0,1));
            links[i].rotate(powf(sin(ofGetFrameNum() / 30.0),i), ofVec3f(0,1,0));
            
            
            links[i].update();

            
            
            ////  squiggly line
            /*
            links[i].rotate(cos(ofGetFrameNum()/400.0), ofVec3f(0,0,1));
            links[i].setScale(0.99);
            links[i].rotate(powf(sin(ofGetFrameNum() / 30.0),2*i), ofVec3f(0,1,0));
*/
            
            //links[i].pitch( powf(sin(ofGetElapsedTimef()),i) );
            //links[i].orbit(powf(sin(ofGetElapsedTimef()),2), powf(sin(ofGetElapsedTimef()),2), 15);
            
            //quat *= powf(sin(ofGetElapsedTimef()),2);
            
            if(links[i].getParent()){
                //links[i].rotateAround(quat, links[i].getParent()->getPosition());
                
            }
            
        }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0,0,0);
    
    ofEnableAlphaBlending();
    ofEnableLighting();
    ofEnableDepthTest();
    
    cam.begin();
    
    
    for(int i=0; i<links.size(); i++) {

        if(links[i].getParent()){
            
            ofLine(links[i].getGlobalPosition(), links[i].getParent()->getGlobalPosition());
        }
        
        
        
        links[i].draw();


        
    }
    
    cam.end();
    
    syphon.publishScreen();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    for(int i=0; i<links.size(); i++) {
        
        /*links[i].setOrientation(
                                links[i].getOrientationEuler() + ofVec3f((int)floor(ofRandom(0,1))*90,0,floor(ofRandom(0,2))*90)
                                
                                );
    */}
    

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
