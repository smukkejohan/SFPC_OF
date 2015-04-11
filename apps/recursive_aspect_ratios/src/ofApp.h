#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

// Scenes recursively create itself next to itself, sometimes branching
// A scene has a set of animation elements and a set of modification properties


// files should be saved from ai as svg tiny 1.2 and responsive off


class Element {
    
public:
    // theese are the possible animation elements, they are loaded frkm svg files
    //ofxSVG svg;
    
    Element(Element * _parent) {
    }
    
    Element(string _path) {
        svg.load(_path);
    }
    
    Element() {
        
        traveling = false;
        col.set(ofRandom(0,255));
    }
    
    //void loadSvg("ofxSVG svg")
    
    ofxSVG svg;
    ofVboMesh * mesh;
    
    ofColor col;
    ofVec3f scale;
    
    
    bool traveling;
    
    void draw() {
        //svg.draw();
        
        ofSetColor(col
                   );
        mesh->drawWireframe();
        
        mesh->draw();
        
    };
    
};


// common data
class Data {
public:
    
    vector<ofTexture *> backgrounds;
    //vector<Element *> baseElements;
    vector<ofVboMesh *> baseMeshes;
    
    int spawnBeats = 0;
    
    Element * getNewElement() {
        Element * el = new Element();
        el->mesh = baseMeshes.at(int(ofRandom(baseMeshes.size())));
        
        //baseElements.push_back(el);
        return el;
        
        //return baseElements.at(int(ofRandom(baseElements.size())));
    }
    
    
    
    
};

// scene is a guy on a bike passing elements in the background
// at some y objects overflow and come back
// different directions ?

class Scene {
public:
    
    bool hasSpace = false;
    bool active = false;
    bool alive = true;
    int attempts = 0;
    
    float fadeIn = 0; // TODO
    
    void findSpace() {
        
        attempts++;
        /*if(attempts>100) {
            alive = false;
            return;
        }*/
        
        // more intelligent testing, store failures
        
        
        width  = int(ofRandom(2,30))*20;
        height = int(ofRandom(4,30))*20;
        
        /*
        if(ofRandom(0.0,1.0) > 0.5) {
            width  = int(ofRandom(2,30))*20;
            height = int(ofRandom(width/20,width/20))*20;
        } else {
         
        }*/
        
        int side = ofRandom(4);
        //int side = 3;
        
        if(side == 0) { // up
            pos = ofVec2f(parent->pos.x + int(ofRandom(-(width/20), width/20))*20, parent->pos.y-height-20);
            
        } else if(side==1) { // right
            pos = ofVec2f(parent->pos.x + parent->width + 20, parent->pos.y + int(ofRandom(-(height/20), height/20))*20);
            
        } else if (side==2) { // down
            pos = ofVec2f(parent->pos.x + int(ofRandom(-(width/20), width/20))*20, parent->pos.y+parent->height+20);
            
        } else { // left
            pos = ofVec2f(parent->pos.x - width - 20, parent->pos.y + int(ofRandom(-(height/20), height/20))*20);
        }
        
        ofRectangle rect = ofRectangle(pos, width, height);
        
        if(root->isSpaceFree(rect)) {
            hasSpace = true;
            active = true;
            
            adjustSize();
            // presever texture scale
            
        }
            
    }
    
    void adjustSize() {
        plane.set(width, height);
        tx0 = 0;
        ty0 = 0;
        tx1 = width/background->getWidth() * 1.2;
        ty1 = height/background->getHeight() * 1.2;// * background->getHeight()/width;

    }
    
    Scene(Data * _data, int _lvl=0, const Scene * _parent=NULL, const Scene * _root=NULL) {
        
        if(!_root) {
            root = this;
        } else {
            root = _root;
        }
        
        parent = _parent;
        data   = _data;
        level  = _lvl;
        
        speed = 8.0f/16.0f;
        time = 1;
        
        plane.setPosition(0, 0, 0);
        plane.setResolution(2, 2);
        
        background = data->backgrounds[ofRandom(data->backgrounds.size()-1)];
        background->setTextureWrap(GL_REPEAT, GL_REPEAT);
        
        if(!parent) {
            hasSpace = true;
            active = true;
            
            width = 40*16;
            height = 40*9;
            pos = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
            adjustSize();
            // this is the root
            
            // choose random elements
            
            elements.push_back(data->getNewElement());
            
            
        } else {
            //parent->speed +
            
            speed = int(ofRandom(1, 16))/16.0;
            
            elements = parent->elements;
            elements.push_back(data->getNewElement());
            
            findSpace();
            
            // Copy data from parent and modify some things slightly
            
        }
        

    }
    //
    
    bool isInViewport() {
        // if not we want to save some resources and maybe kill the data
    }
    
    bool isSpaceFree(ofRectangle _rect) const {
        // go all the way down the tree to ask if this rectangle intersects with children
        
        if (_rect.intersects(ofRectangle(pos-ofVec2f(20,20), width+40, height+40))) {
            return false;
            
        } else if(children.size() > 0) {
            
            for(int i=0; i<children.size(); i++) {
                if (!children[i]->isSpaceFree(_rect) && children[i]->hasSpace) {
                    return false;
                }
            }
            return true;
            
        } else {
            return true;
        }
        
        return true;
        
    }
    
    ofPlanePrimitive plane;
    
    int level;
    Data * data;
    const Scene * parent;
    const Scene * root;
    
    vector<Scene *> children;
    vector<Element *> elements;
    
    ofTexture * background;
    float tx0, ty0, tx1, ty1;
    
    ofVec2f pos;
    int width;
    int height;
    // todo: img tileable
    
    void debugDraw() {
        
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        
        ofSetColor(200, 200, 200, 100);
        ofNoFill();
        ofDrawRectangle(0, 0, width, height);
        ofDrawBitmapString("Scene lvl " + ofToString(level),0,0);
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    void draw() {
        
        if(active) {
            
            plane.mapTexCoords(tx0 + time/1000.0, ty0, tx1 + time/1000.0, ty1);
            
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(pos);
            
            ofFill();
            ofSetColor(100,100,100);

            ofDrawRectangle(-2, -2, width+4, height+4);
            
            ofPushMatrix();
            ofSetColor(255,255,255);
            ofTranslate(width/2, height/2);
            
            background->bind();
            plane.draw();
            background->unbind();
            

            
            
            ofPopMatrix();
            
            
            for(int i=0; i<elements.size(); i++) {
                ofPushMatrix();
                ofTranslate(100 + i*100, height/2);
                
                //ofEnableLighting();
                ofSetColor(255);
                elements[i]->draw();
                ofPopMatrix();
                
            }
            
            
            ofPopMatrix();
            ofPopStyle();
        
        // Loop through elmenents and draw them
            
            for(int i=0; i<children.size(); i++) {
                children[i]->draw();
            }
            
        }
        
        
        //debugDraw();
        
        
        // for all chilren draw
    };
    
    // maybe add a global speed
    
    void spawn() {
        
        if(active && data->spawnBeats > 0) {
            
            if(children.size() < 3) {
                
                if(time>2000*children.size()*max(level,1)&& level < 4) {
                    //cout<<"give birth"<<endl;
                    if(ofRandom(0.0,1.0) < 0.5) {
                        Scene * child = new Scene(data, level+1, this, root);
                        children.push_back(child);
                        
                        data->spawnBeats--;
                        
                    }
                    
                }
            }
        }
    }
    
    void update() {
        
        if(!hasSpace) {
            findSpace();
        }
        
        if(active) {
            time += speed * ofGetLastFrameTime() * 1000.0f;
        
            // call element update
        
            // if elements are out of scene shuffle around to the other end
            // if element on playline - have a sample
        
            for(int i=0; i<children.size(); i++) {
                children[i]->update();
            }
            
            spawn();
        
        }
        
        
        // at a certain point recurse
        // maybe twice but not more
        
        
        // at a certain point die
        
        
        // die if out of view
        
    };
    
    float speed;
    unsigned long int time;
    
};


class ofApp : public ofBaseApp{

	public:
    
    void loadAnimations();
    
    void drawScenes();
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    Scene * root;
    
    unsigned long int time;
    unsigned long int lastTime;
    float speed;
    
    Data * data;
    
    ofCamera cam;
    
    ofVec3f camPos;
    
};
