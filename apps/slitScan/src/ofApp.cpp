#include "ofApp.h"

#define WIDTH 1920/2
#define HEIGHT 1080/2


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    
    //distortionMap.loadImage("distortion.png");
    //distortionMap.resize(1920, 1080);
    
    ofFbo::Settings fboSettings;
    fboSettings.height = HEIGHT;
    fboSettings.width = WIDTH;
    //fboSettings.numSamples = 1;
    fboSettings.useDepth = false;
    //fboSettings.internalformat = GL_RGB;
    
    //fboSettings.
    inputFbo.allocate(fboSettings);
    
    //moviePixels.allocate(WIDTH, HEIGHT);
    inputFbo.readToPixels(moviePixels);
    
    //moviePixels.setImageType(OF_IMAGE_GRAYSCALE);
    
    mapFbo.allocate(fboSettings);
    mapFbo.readToPixels(mapPixels);
    
    movieImage.allocate(WIDTH, HEIGHT, OF_IMAGE_COLOR);
    
    //player.load
    
    //moviePixels.setNumChannels(1);
    
    //set up a slit scan with a maximum capacity of frames
    // in the distortion buffer
    slitScan.setup(WIDTH, HEIGHT, 120);
    
    slitScan.setDelayMap(mapPixels);
    //blending means the edges between the scans are feathered
    slitScan.setBlending(true);
    
    //time delay is the deepest in history the delay can go
    //and width is the number of frames the distortion will encompass
    //note that the delay cannot be more than the total capacity
    
    //set up the grabber
    //grabber.initGrabber(1920, 1080);
    
    gui = new ofxUICanvas();
    gui->addSlider("Delay", 0, 200, &delay);
    gui->addSlider("Width", 0, 400, &width);
    
    directory.setup();
    
    syphonDisplacementMapIn.setApplicationName("Millumin");
    syphonDisplacementMapIn.setServerName("Screen 2");
    syphonDisplacementMapIn.setup();
    
    syphonMovieIn.setApplicationName("Millumin");
    syphonMovieIn.setServerName("Screen 1");
    syphonMovieIn.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    slitScan.setTimeDelayAndWidth(delay, width);
    

    //grabber.update();
    
    //if(grabber.isFrameNew()){
    
    //}
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    mapFbo.begin();
    //distortionMap.draw(0,0);
    ofBackground(255);
    syphonDisplacementMapIn.draw(0,0);
    mapFbo.end();
    mapFbo.readToPixels(mapPixels);
    slitScan.setDelayMap(mapPixels);
    
    
    
    inputFbo.begin();
    ofBackground(0);
    syphonMovieIn.draw(0, 0);
    inputFbo.end();
    
    inputFbo.readToPixels(moviePixels);
    
    movieImage.setFromPixels(moviePixels);
    //movieImage.setFromPixels(moviePixels);
    //slitScan.addImage(moviePixels);
    slitScan.addImage(movieImage);
    ofSetColor(255);
    
    
    //movieImage.draw(0,0);
    slitScan.getOutputImage().draw(0, 0);
    
    ofSetColor(255);
    
    mapFbo.draw(200, 0, WIDTH/10, HEIGHT/10);
    
    inputFbo.draw(400, 0,WIDTH/10, HEIGHT/10);
    

    
    syphonOut.publishTexture(&slitScan.getOutputImage().getTexture());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'm') {
        dirIdMovie++;
        if(dirIdMovie > directory.size() - 1)
            dirIdMovie = 0;
        
        if(directory.isValidIndex(dirIdMovie)){
            syphonMovieIn.setServerName(directory.getServerList()[dirIdMovie].serverName);
            syphonMovieIn.setApplicationName(directory.getServerList()[dirIdMovie].appName);
        }
    }
    
    if(key == 'n') {
        dirIdMap++;
        if(dirIdMap > directory.size() - 1)
            dirIdMap = 0;
        
        if(directory.isValidIndex(dirIdMap)){
            syphonDisplacementMapIn.setServerName(directory.getServerList()[dirIdMap].serverName);
            syphonDisplacementMapIn.setApplicationName(directory.getServerList()[dirIdMap].appName);
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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


void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdMap = 0;
    dirIdMovie = 0;
}

void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdMap = 0;
    dirIdMovie = 0;
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdMap = 0;
    dirIdMovie = 0;
}