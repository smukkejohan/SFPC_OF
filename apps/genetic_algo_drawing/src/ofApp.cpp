#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
   
        
        
        
        setupSimulation();



}


float Population::getFitness() {
    
    float diff = 0;
    for (int p = 0; p < targetImg.getPixels().size(); p++) {
        int  dp = targetImg.getPixels()[p] - pixels[p];
        diff += dp * dp;
    }
    
    
    fitness = 1 - diff / (targetImg.getPixels().size() * 256 * 256);
    
    
}

void ofApp::setupSimulation() {
    
        population = new Population(popSize, "target.jpg");
    
}



//--------------------------------------------------------------
void ofApp::update(){

    

    

    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    
    population->targetImg.draw(0,0, targetImage.width, targetImage.height);
    population->fbo.draw(0,0);
    
    
    
    
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
