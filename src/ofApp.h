#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxMaxim.h"
#include "maxiGrains.h"
#include "ofxOsc.h"
#include <sys/time.h>

#define HOST "localhost"
#define RECEIVEPORT 12000
#define SENDPORT 6448

typedef hannWinFunctor grainPlayerWin;


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void arc(float p,float radius);
    
    
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
    
    float phase;
    int spacing;

    
    int        bufferSize;
    int        initialBufferSize; /* buffer size */
    int        sampleRate;
    
    
    // set up  maximilian stuff
    
    double wave,sample,outputs[2];
    maxiSample sound, sound2, sound3, sound4, sound5;
    vector<maxiTimePitchStretch<grainPlayerWin, maxiSample>*> stretches;
    maxiMix mymix;
    maxiTimePitchStretch<grainPlayerWin, maxiSample> *ts, *ts2 ,*ts3, *ts4, *ts5;
    double speed, length;
    
    ofxMaxiFFT fft;
    ofxMaxiFFTOctaveAnalyzer oct;
    int current;
    double pos;
    
    //osc
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    ofxMaxiFilter myFilter, myFilter2; 
    bool mouseMove;
    
    
};
