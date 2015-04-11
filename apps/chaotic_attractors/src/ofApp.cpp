#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mesh.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    //for(int i=0; i<400; i++) {
    
    //attractor.iterate();
    
    /*if(attractor.I % 200 == 0 && attractor.I > 40000) {
        mesh.clear();
        for(int i=0; i<attractor.d.size(); i++){
            float x = ofGetWidth() * (attractor.d[i].x - attractor.xmin) / (attractor.xmax-attractor.xmin);
            float y = ofGetHeight() * (attractor.d[i].y - attractor.ymin) / (attractor.ymax-attractor.ymin);
            mesh.addVertex(ofVec2f(x,y));
        }

    }*/
    
    
    if(!attractor.drawIt) {
        //cout<<attractor.type<<endl;
        attractor.setup();
    }
        
    //}
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //if(attractor.drawIt && attractor.I > 200) {
    //if(attractor.drawIt) {
        ofBackground(40,40,40);
        ofSetColor(220,220,220,180);
    
    
    
    
    attractor.lock();
    
        ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofScale(400,400);
    
    if(attractor.mesh.getNumVertices() > 0) {
        attractor.mesh.draw();
    }
    
        ofPopMatrix();
        
        ofDrawBitmapString(ofToString(attractor.I) + " " + attractor.type + " " + ofToString(attractor.seed), 20,20);
    
    attractor.unlock();
    //}
    //}
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
