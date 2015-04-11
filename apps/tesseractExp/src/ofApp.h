#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTesseract.h"
#include "CvUtils.h"
#include "ofxOpenCv.h"

using namespace cv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		string runOcr(float scale, int medianSize);
		
		ofxTesseract tess;
		ofImage img, scaled;
		string ocrResult;

        ofxFloatSlider scale;
        ofxIntSlider medianSize;
    
        
        ofxFloatSlider brightness;
    ofxFloatSlider contrast;

        ofxButton process;
    ofxButton snap;

        ofxPanel gui;

        void processButtonPressed();
    
        void snapButtonPressed();
    
        ofVideoGrabber 		vidGrabber;
    
    int 				camWidth;
    int 				camHeight;
    
    ofPixels input;
    ofTexture			videoTexture;
    

    ofxCvColorImage colImg;
    ofxCvGrayscaleImage grayImg;
   
    
    
};
