#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /* if using macbook retina, set to true */
    bool retina = true;
    
    
    radius = 120.0;
    maxRadius = 200.0;

    /* setup a grab window, same size as the app */
    grabber.setup(maxRadius*2, maxRadius*2, retina);
    
    canvas.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    
    int numPts  = 20;
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
        float tx = ofMap( px, -1.0, 1.0, 0, maxRadius*2) ;
        float ty = ofMap( py, -1.0, 1.0, 0, maxRadius*2) ;
        //float d = ofRandom(-circleTexture.getWidth()/2, circleTexture.getWidth()/2);
        //float d = 0;
        NormCircleCoords.push_back( ofPoint(tx, ty) );
        //angle += step;
    }
    
    
    framerate = 30;
    maxFrames = 1;
    
    
    //frame =
    
    
    MacGLUTFix(true);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    /* grab screen starting at (0, 0) */
    
    // TODO fix the corners
    
    int x = -maxRadius+mouseX+ofGetWindowPositionX();
    int y = -maxRadius+mouseY+ofGetWindowPositionY();
    
    grabber.grabScreen(max(0,x), max(0,y));
    
    
    radius = 120 + ofSignedNoise(ofGetElapsedTimef()) * 20;
}

//------------------------------------------------- -------------
void ofApp::draw(){

    
    while(frames.size() < maxFrames) {
        frames.push_back(Frame());
    }
    
    while(frames.size() > maxFrames) {
        frames.pop_back();
    }
    
    
    int currentFrame = ofGetFrameNum() % maxFrames;
    
    //cout<<currentFrame<<endl;
    
    
    /*frames[currentFrame].begin();{
        
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
        
        
    }frames[currentFrame].end();*/

    //frames[currentFrame].draw(0,0);

    
    // Feedback draw not saved
    
    ofPushMatrix();
    ofTranslate(mouseX, mouseY);
    
    // draw brush shapes using a shader
    grabber.draw(-maxRadius, -maxRadius);
    
    /*tex.bind();
    glBegin(GL_POLYGON); {
        for(int i = 0; i < NormCirclePts.size(); i++){
            glTexCoord2f(NormCircleCoords[i].x * radius/maxRadius*2, NormCircleCoords[i].y * radius/maxRadius*2);
            
            glVertex2f( NormCirclePts[i].x * radius,  NormCirclePts[i].y * radius);
        }
    } glEnd();
    tex.unbind();*/
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    // todo handle corners
    //cout<<"grab"<<endl;
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
