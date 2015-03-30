#pragma once

#include "ofMain.h"


// based on https://github.com/ChrisCummins/chriscummins.github.io/blob/master/js/genetics.js

class Individual {
public:
    
    
    Individual() {
        
        // random
        
        verts.push_back(
                               ofPoint(ofRandomf(), ofRandomf()));
        verts.push_back(
                               ofPoint(ofRandomf(), ofRandomf()));
        verts.push_back(
                               ofPoint(ofRandomf(), ofRandomf()));
        
        col = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
        
        //fitness = 1;
        
        
    }
    
    Individual(const Individual * mother, const Individual * father) {
        
    }
    
    bool operator < (const Individual& b) const
    {
        return (fitness < b.fitness);
    }
    
    
    void draw() {
        
            ofSetColor(col);
            ofBeginShape();
            ofVertices(verts);
            ofEndShape();
        
    }
    
    vector<ofPoint> verts;
    ofColor col;
    float fitness;
};


class Population {
public:
    Population(int _size, string targetImgPath) {
        
        size = _size;
        
        targetImg.load(targetImgPath);
        
        fbo.allocate(targetImg.width, targetImg.height);
        
        for (int i=0; i<_size;i++) {
            individuals.push_back(new Individual());
        }
        
        
        // defaults
        
        selectionCutoff = 0.15;
        
        
    };
    
    void draw() {
        
        fbo.begin();
        ofBackground(0,0,0);
        ofSetColor(255);
        
        ofPushMatrix();
        ofScale(targetImg.width, targetImg.height);
        for(int i=0; i<individuals.size(); i++) {
            individuals[i]->draw();
        }
        ofPopMatrix();
        
        fbo.end();
        fbo.readToPixels(pixels);

    }
    
    
    void iterate() {
      
        vector<Individual *> offspring;
        
        
        /* The number of individuals from the current generation to select for
         * breeding
         */
        int selectCount = floor(size * selectionCutoff);
        
        
        // number to randomly generate
        int randCount = ceil(1.0f / selectionCutoff);
        
        
        // sort individuals by fitness
        sort(individuals.begin(), individuals.end());
        
        
        if (fittestSurvive)
            randCount--;
        
        
        for (int i = 0; i < selectCount; i++) {
        
            for (int j = 0; j < randCount; j++) {
                int randIndividual = i;
                
                
                while (randIndividual == i) {
                    randIndividual = (ofRandomf() * selectCount);
                }
                
                offspring.push_back(new Individual(individuals[i], individuals[randIndividual]));
            
            
            }
        
        }
        
        
        if (fittestSurvive) {
            individuals.insert(individuals.end(), offspring.begin(), offspring.end());
        } else {
            individuals = offspring;
        }
        
    };
    
    int size;
    float selectionCutoff;
    
    vector<Individual *> individuals;
    
    ofFbo fbo;
    ofPixels pixels;
    
    float fitness;
    
    float mutationChance;
    float mutateAmount;
    
    bool fittestSurvive = true;
    
    float getFitness();
    
    
    ofImage targetImg;
    
};



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    
    
    void setupSimulation();
    
    //void mutateShape(Shape shape);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    int popSize = 50;
    

    
    
    ofImage targetImage;
    
    Population * population;
		
};


