#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    ofSetFrameRate(30);
    
    lastTime = 0;
    time = 0;
    speed = 1.0f;
    
    data = new Data();
    ofDirectory bgDir = ofDirectory("bg");
    //cout<<bgDir.getAbsolutePath()<<endl;
    bgDir.listDir();
    int size = bgDir.size();
    
    for(int i=0; i<size; i++) {
        ofLogNotice()<<"Loading background tile "<<bgDir.getFiles()[i].path()<<endl;
        
        ofImage bg; bg.load(bgDir.getFiles()[i]);
        ofTexture * tex = new ofTexture();
        ofPixels pix; bg.getTexture().readToPixels(pix);
        tex->loadData(pix);
        data->backgrounds.push_back(tex);
    }
    
    // set up some elements
    //Element * cube = new Element("svg/cube01.svg");
    //data->baseElements.push_back(cube);
    
    ofBoxPrimitive boxprim = ofBoxPrimitive(80, 80, 80);
    data->baseMeshes.push_back(new ofVboMesh(boxprim.getMesh()));
    
    ofSpherePrimitive sphereprim = ofSpherePrimitive(40, 20);
    data->baseMeshes.push_back(new ofVboMesh(sphereprim.getMesh()));
    
    ofCylinderPrimitive cylprim = ofCylinderPrimitive(40, 60, 20, 4);
    data->baseMeshes.push_back(new ofVboMesh(cylprim.getMesh()));
    
    
    root = new Scene(data);
    
    // setup the first root scene - the rest is recursion
    
    camPos = ofVec3f(ofGetWidth()/2,ofGetHeight()/2,-400);
    
    cam.setupPerspective();
    
    cam.setPosition(camPos);
    
}

//--------------------------------------------------------------
void ofApp::update(){
           
    time += speed * ofGetLastFrameTime() * 1000.0f;
    
    root->update();
    
    if(time-lastTime > 2000) {
        data->spawnBeats++;
        lastTime = time;
    }
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
        //svg.draw();
    ofBackground(0,0,0);
    camPos.z--;
    //cout<<time<<endl;
    cam.lookAt(ofVec3f(ofGetWidth()/2,ofGetHeight()/2,0));
    cam.setPosition(camPos);
    
    cam.begin();
    ofPushMatrix();
    
    //ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    root->draw();
    
    ofPopMatrix();
    
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
