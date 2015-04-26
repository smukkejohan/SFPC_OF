#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	tracker.setup();
	tracker.setRescale(.5);
    
    matrix1.allocate(8, 8, OF_IMAGE_GRAYSCALE);
    eye.allocate(8, 8);
    pix.allocate(8, 8, OF_IMAGE_GRAYSCALE);

    
    eyeOpen.loadImage("eye.png");
    eyeClosed.loadImage("eye-closed.png");
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    serial.setup(0, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) {
			classifier.classify(tracker);
		}
	}
    
    
    
}

void testApp::draw() {
    
    //matrix1.loadImage(<#string fileName#>);
    
    eye.begin();
    
    ofBackground(0);
    ofSetColor(255);
    
    
   /* glBegin(GL_POINTS);
    glVertex2d(ofMap(mouseX, 0, 200, 0, 8, true), ofMap(mouseY, 0, 200, 0, 8, true));
    glEnd();
    */
/*
    // happy smiley
    ofNoFill();
    ofCircle(4, 4, 3.5);
    
    glBegin(GL_POINTS);
    glVertex2d(2, 2);
    glVertex2d(5, 2);
    glVertex2d(5, 4);
    glVertex2d(4, 5);
    glVertex2d(3, 5);
    glVertex2d(2, 4);
    glEnd();
    
    
    ofCircle(4, 4, 3.5);*/
    
    //ofNoFill();
    
   /*
    glBegin(GL_POINTS);
    glVertex2d(2, 2);
    glVertex2d(5, 2);
    glVertex2d(5, 4);
    glVertex2d(4, 5);
    glVertex2d(3, 5);
    glVertex2d(2, 4);
    glEnd();
    */
    
    if(ofGetFrameNum() % 30 < 24) {
        eyeClosed.draw(0,0, 8, 8);
    } else {
        eyeOpen.draw(0, 0, 8, 8);

    }
    
    eye.end();
    
    eye.readToPixels(pix);
    matrix1.setFromPixels(pix);
    
	ofSetColor(255);
	cam.draw(0, 0);
	tracker.draw();
	
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();
  for(int i = 0; i < n; i++){
		ofSetColor(i == primary ? ofColor::red : ofColor::black);
		ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
  }
	ofPopMatrix();
	ofPopStyle();
	
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	drawHighlightString(
		string() +
		"r - reset\n" +
		"e - add expression\n" +
		"a - add sample\n" +
		"s - save expressions\n"
		"l - load expressions",
		14, ofGetHeight() - 7 * 12);
    
    
    ofSetColor(255);
    
    //eye.draw(0, 0, 100, 100);
    matrix1.draw(0,0,200,200);
    
    
    
    if(ofGetFrameNum() % 1 == 0) {
        
        for(int r=0; r<matrix1.getHeight(); r++) {
            //int bitSum;
            
            char bin[8];
            
            for(int c=0; c<matrix1.getWidth(); c++) {
                if(matrix1.getColor(r, c).getBrightness() > 128) {
                    bin[c] = 1;
                } else {
                    bin[c] = 0;
                }
            }
            
            char val = 0;
            for(int i=0; i<8; i++)
            {
                val = val*2;
                val = val + bin[i];
            }
            
            serial.writeByte(val);
            
        }
        
        serial.writeByte('\n');
    }

    
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
	if(key == 'e') {
		classifier.addExpression();
	}
	if(key == 'a') {
		classifier.addSample(tracker);
	}
	if(key == 's') {
		classifier.save("expressions");
	}
	if(key == 'l') {
		classifier.load("expressions");
	}
    
    if(key == 'c') {
        

        
        
    }
    
    
}