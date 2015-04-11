//
//  screenGrab.h
//  example_ofwindow
//
//  Created by Johan Bichel Lindegaard on 4/2/15.
//
//

#pragma once

#include "ofMain.h"


extern unsigned char * pixelsBelowWindow(int x, int y, int w, int h);

extern void setWindowTransparent();

class ScreenGrab
{
public:
    void setup(int width, int height, bool retina=false);
    void grabScreen(int x, int y);
    void grabScreen() {grabScreen(0, 0);}
    void draw(int x, int y, int w, int h);
    void draw(int x, int y) {draw(x, y, width, height);}
    ofTexture& getTextureReference() {return tex;}
    
private:
    int width, height;
    ofTexture tex;
    int rx;
};
