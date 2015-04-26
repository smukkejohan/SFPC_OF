#include "ofMain.h"
#include "ofApp.h"

#include "ofxCocoa.h"
#include <Cocoa/Cocoa.h>

//========================================================================
int main()
{
	
	MSA::ofxCocoa::InitSettings			initSettings;
	initSettings.isOpaque				= true;
	initSettings.windowLevel			= kCGMaximumWindowLevelKey;
	initSettings.hasWindowShadow		= false;
	initSettings.numFSAASamples			= true;
	initSettings.initRect.size.width	= 1600;
	initSettings.initRect.size.height	= 1050;
    initSettings.initRect.origin.x      = 0;
    initSettings.initRect.origin.y      = 0;
    
	initSettings.windowMode				= OF_WINDOW;
	
	// to go fullscreen across all windows:
	initSettings.windowStyle			= NSBorderlessWindowMask;
	initSettings.initRect				= MSA::ofxCocoa::rectForMainScreen();
//	initSettings.initRect				= MSA::ofxCocoa::rectForAllScreens();
    
    MSA::ofxCocoa::setSyncToDisplayLink(true);
    MSA::ofxCocoa::setCaptureExternalMouseEvents(true);
    
	MSA::ofxCocoa::AppWindow		cocoaWindow(initSettings);
    
	ofSetupOpenGL(&cocoaWindow, 0, 0, OF_WINDOW);
    
    //MSA::ofxCocoa::glWindow()
    //MSA::ofxCocoa::setCaptureExternalMouseEvents(true);
        
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
	ofRunApp( new ofApp() );
	
}
