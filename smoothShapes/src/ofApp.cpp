#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    float cd = 0.1; // corner dist, how wide are the corners
    //float width = 1;
    //float height = 1;
    
    float smoothness = 10; // how many subdivisions in the corner
    
    // normalize from -1 to 1 to make scaling around 0 easy
    
    // from -1,-1
    smoothrect.addVertex(-1+cd, -1);
    smoothrect.lineTo(1-cd, -1);
    smoothrect.bezierTo(1, -1, 1, -1, 1, -1+cd, smoothness);
    
    // to 1,1
    smoothrect.lineTo(1, 1-cd);
    smoothrect.bezierTo(1, 1, 1, 1, 1-cd, 1, smoothness);
    
    // to 0,0
    smoothrect.lineTo(-1+cd, 1);
    smoothrect.bezierTo(-1, 1, -1, 1, -1, 1-cd, smoothness);
    
    // back to 0,0
    smoothrect.lineTo(-1, -1+cd);
    smoothrect.bezierTo(-1, -1, -1, -1, -1+cd, -1, smoothness);
    
    
    smoothRectAsMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    for(int i=0; i<smoothrect.size(); i++) {
        smoothRectAsMesh.addVertex(smoothrect[i]);
        //smoothRectAsMesh.addVertex(smoothrect[i]*1.1);
    }
    
    smoothRectHollowAsMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for(int i=0; i<smoothrect.size(); i++) {
        smoothRectHollowAsMesh.addVertex(smoothrect[i]);
        // scale the vertices down to create the inner contour of the frame
        // 0.8 = border will be 20% width
        smoothRectHollowAsMesh.addVertex(smoothrect[i]*0.8);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(120,120);
    ofScale(100,100);
    
    //
    // Use set line width to draw, better than ofDrawRectangleRounded
    // but still kind of jerky
    
    ofSetLineWidth(200);
    smoothrect.draw();
    
    ofPopStyle();
    ofPopMatrix();
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(380,120);
    ofScale(100,100);
    
    //
    // Use a mesh to draw it, very smooth corners
    ofSetColor(0);
    smoothRectAsMesh.draw();
    
    ofSetColor(100,100,100,80);
    smoothRectAsMesh.drawWireframe();
    
    ofPopStyle();
    ofPopMatrix();
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(120,380);
    ofScale(100,100);
    
    //
    // Draw
    ofSetColor(0);
    smoothRectHollowAsMesh.draw();
    ofSetColor(100,100,100,80);
    smoothRectHollowAsMesh.drawWireframe();
    
    ofPopStyle();
    ofPopMatrix();
    
    
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
