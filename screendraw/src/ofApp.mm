#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /* if using macbook retina, set to true */
    bool retina = true;
    
    
    radius = 120;
    maxRadius = 200;

    /* setup a grab window, same size as the app */
    grabber.setup(maxRadius, maxRadius, retina);
    
    canvas.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    
    int numPts  = 10;
    float angle = 0.0;
    float step  = TWO_PI / (float)(numPts-1);

    for(int i = 0; i < numPts; i++){
        
        float angle = ofMap(i, 0, numPts-1, 0.0, TWO_PI);

        //get the -1 to 1 values - we will use these for drawing our pts.
        float px = cos(angle);
        float py = sin(angle);
        
        NormCirclePts.push_back( ofPoint(px, py) );
        //map the -1 to 1 range produced by cos/sin
        //to the dimensions of the image we need for our texture coords
        float tx = ofMap( px, -1.0, 1.0, 0, maxRadius) ;
        float ty = ofMap( py, -1.0, 1.0, 0, maxRadius) ;
        //float d = ofRandom(-circleTexture.getWidth()/2, circleTexture.getWidth()/2);
        //float d = 0;
        NormCircleCoords.push_back( ofPoint(tx, ty) );
        //angle += step;
    }
    
    
    framerate = 30;
    maxFrames = 1;
    
    
    //frame =
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    /* grab screen starting at (0, 0) */
    

}

//------------------------------------------------- -------------
void ofApp::draw(){

    /* or you can get the texture directly */
    
    
    while(frames.size() < maxFrames) {
        frames.push_back(Frame());
    }
    
    while(frames.size() > maxFrames) {
        frames.pop_back();
    }
    
    
    int currentFrame = ofGetFrameNum() % maxFrames;
    
    cout<<currentFrame<<endl;
    
    
    frames[currentFrame].begin();{
        
        if(ofGetMousePressed()) {
        ofPushMatrix();
        ofTranslate(mouseX, mouseY);
        
        tex.bind();
        glBegin(GL_POLYGON); {
            for(int i = 0; i < NormCirclePts.size(); i++){
                glTexCoord2f(NormCircleCoords[i].x, NormCircleCoords[i].y);
                glVertex2f( NormCirclePts[i].x * radius,  NormCirclePts[i].y * radius);
            }
        } glEnd();
        tex.unbind();
            ofPopMatrix();
        }
        
        
    }frames[currentFrame].end();

    
    frames[currentFrame].draw(0,0);
    
    // Feedback draw not saved
    
    ofPushMatrix();
    ofTranslate(mouseX, mouseY);

    tex.bind();
    glBegin(GL_POLYGON); {
        for(int i = 0; i < NormCirclePts.size(); i++){
            glTexCoord2f(NormCircleCoords[i].x, NormCircleCoords[i].y);
            glVertex2f( NormCirclePts[i].x * radius,  NormCirclePts[i].y * radius);
        }
    } glEnd();
    tex.unbind();
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
        grabber.grabScreen(max(0,-radius+mouseX+ofGetWindowPositionX()), max(0,-radius+mouseY+ofGetWindowPositionY()));
    
    
    cout<<"grab"<<endl;
    ofPixels pix;
    grabber.getTextureReference().readToPixels(pix);
    tex.loadData(pix);

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
