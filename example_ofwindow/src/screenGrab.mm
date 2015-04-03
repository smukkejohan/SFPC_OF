//
//  screenGrab.cpp
//  example_ofwindow
//
//  Created by Johan Bichel Lindegaard on 4/2/15.
//
//

#include "screenGrab.h"

//-------------
void ScreenGrab::setup(int width, int height, bool retina) {
    this->width = width;
    this->height = height;
    if (retina) rx = 2;
    else        rx = 1;
    tex.allocate(rx * width, rx * height, GL_RGBA);
}

//-------------
void ScreenGrab::grabScreen(int x, int y) {
    unsigned char * data = pixelsBelowWindow(x, y, width, height);
    for (int i = 0; i < rx*rx*width*height; i++){
        unsigned char r1 = data[i*4];
        data[i*4]   = data[i*4+1];
        data[i*4+1] = data[i*4+2];
        data[i*4+2] = data[i*4+3];
        data[i*4+3] = r1;
    }
    if (data!= NULL) tex.loadData(data, rx*width, rx*height, GL_RGBA);
}

//-------------
void ScreenGrab::draw(int x, int y, int w, int h) {
    tex.draw(x, y, w, h);
}


void setWindowTransparent() {

// Get the CGWindowID of supplied window
NSOpenGLContext * myContext = nil;
NSView *myView = nil;
NSWindow* window = nil;

// In screensaver mode, set our window's level just above
// our BOINC screensaver's window level so it can appear
// over it.  This doesn't interfere with the screensaver
// password dialog because the dialog appears only after
// our screensaver is closed.
myContext = [ NSOpenGLContext currentContext ];
if (myContext)
myView = [ myContext view ];
if (myView)
window = [ myView window ];
if (window == nil)
return NULL;
    
    
    [window setIgnoresMouseEvents:YES];



}

CGImageRef capturedImage;

unsigned char * pixelsBelowWindow(int x, int y, int w, int h)
{
    // Get the CGWindowID of supplied window
    NSOpenGLContext * myContext = nil;
    NSView *myView = nil;
    NSWindow* window = nil;
    
    // In screensaver mode, set our window's level just above
    // our BOINC screensaver's window level so it can appear
    // over it.  This doesn't interfere with the screensaver
    // password dialog because the dialog appears only after
    // our screensaver is closed.
    myContext = [ NSOpenGLContext currentContext ];
    if (myContext)
        myView = [ myContext view ];
    if (myView)
        window = [ myView window ];
    if (window == nil)
        return NULL;
    
     [window setIgnoresMouseEvents:YES];
    // For some reason we need to do this all the time ??
    //[window setCaptureExternalMouseEvents:YES];
    
    CGWindowID windowID = [window windowNumber];
    
    // Get window's rect in flipped screen coordinates
    CGRect windowRect = NSRectToCGRect( [window frame] );
    windowRect.origin.y = NSMaxY([[window screen] frame]) - NSMaxY([window frame]);
    
    windowRect.origin.x = x;
    windowRect.origin.y = y;
    windowRect.size.width = w;
    windowRect.size.height = h;
    
    // Get a composite image of all the windows beneath your window
    capturedImage = CGWindowListCreateImage( windowRect, kCGWindowListOptionOnScreenBelowWindow, windowID, kCGWindowImageDefault );
    
    // The rest is as in the previous example...
    if(CGImageGetWidth(capturedImage) <= 1) {
        CGImageRelease(capturedImage);
        //return nil;
        return NULL;
    }
    
    // Create a bitmap rep from the window and convert to NSImage...
    NSBitmapImageRep *bitmapRep = [[[NSBitmapImageRep alloc] initWithCGImage: capturedImage] autorelease];
    NSImage *image = [[[NSImage alloc] init] autorelease];
    [image addRepresentation: bitmapRep];
    
    uint32* bitmapPixels = (uint32*) [bitmapRep bitmapData];
    
    CGImageRelease(capturedImage);
    return (unsigned char *) bitmapPixels;
    //return image;
}
