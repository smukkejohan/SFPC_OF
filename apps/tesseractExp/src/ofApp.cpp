#include "ofApp.h"

void ofApp::setup(){
    
    camWidth 		= 320*2;	// try to grab at this size.
    camHeight 		= 240*2;
    
    gui.setup(); // most of the time you don't need a name
    
    snap.addListener(this,&ofApp::processButtonPressed);
    
	process.addListener(this,&ofApp::processButtonPressed);

	gui.add(scale.setup( "scale", 2.5, 1, 4 ));
	gui.add(medianSize.setup( "medianSize", 2, 0, 12 ));
	gui.add(process.setup("process"));
    
    
    gui.add(contrast.setup( "Contrast", 0.0, 0, 1 ));
    gui.add(brightness.setup( "Brightness", 0.0, 0, 1 ));
    
    gui.add(snap.setup("process"));
    

	tess.setup();
	tess.setWhitelist("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,");
	tess.setAccuracy(ofxTesseract::ACCURATE);
	tess.setMode(ofxTesseract::AUTO);
    

    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    
    //grayImg.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
    input.setImageType(OF_IMAGE_GRAYSCALE);
    videoTexture.allocate(camWidth,camHeight, GL_RGB);
    
    
    
    colImg.allocate(camWidth, camHeight);
    grayImg.allocate(camWidth, camHeight);
    
    //ocrResult = runOcr(scale, medianSize);
}

void ofApp::processButtonPressed()
{
    
    ocrResult = runOcr(scale, medianSize);
}

void ofApp::update(){
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()) {
        input = vidGrabber.getPixelsRef();
        
        colImg.setFromPixels(input);
        
        grayImg.setFromPixels(input);
        //ofImage = img;
        //img.setFromPixels(input);
        grayImg = colImg;
        
        grayImg.brightnessContrast(contrast,brightness);
        
        //grayImg.setImageType(OF_IMAGE_GRAYSCALE);
    
    
    }
}


void ofApp::draw(){
	ofPushMatrix();
	
	ofTranslate(300, 0);
	
	ofSetColor(0);	
	vector<string> lines = ofSplitString(ocrResult, "\n");
	for(int i = 0; i < lines.size(); i++) {
		ofDrawBitmapString(lines[i], 10, 20 + i * 12);
	}
	ofSetColor(255);
	vidGrabber.draw(0, 10);
    grayImg.draw(400, 10);
	scaled.draw(0, 400);
	
	ofPopMatrix();

    gui.draw();

}

// depending on the source of the text you want to OCR,
// you might need to preprocess it. here i'm doing a
// simple resize followed by a median blur.
string ofApp::runOcr(float scale, int medianSize) {

    
    
    scaled.setFromPixels(grayImg.getPixelsRef());
	//scaled = grayImg;
	
	// resize and median blur the image
	scaled.resize(grayImg.getWidth() * scale, grayImg.getHeight() * scale);
    

	//medianBlur(scaled, medianSize);
    
	return tess.findText(scaled);
}

