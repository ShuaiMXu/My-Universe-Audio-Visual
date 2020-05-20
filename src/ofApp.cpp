
/*    << My universe>>  https://vimeo.com/311140573
 
 
 My universe has five Sounds we can use, five sounds like a timeline from past to now, the first sound like ancient times, everything is chaotic and invisible, everything is the most primitive.
 
 
 The Second sound revolves around the human voice, like the beginning of human beings, and seeks the most primitive sound.
 

 The third sound into industrialization, starting to have a crashing sound.
 

 The Fourth sound, in the era of technology, in the voice, we can feel some original technology.
 

 The fifth sound, like a digital area, everything we can not know, also like an alien voice or code real voice.
 

 Two parts about My universe
 

 1.Dream (Everything is illusory and cannot be changed)
 

 2.Real life (Everything is real and you can control everything)
 

 ------------------ Techniques used ------------------

 1.Press “Q” into Dream order
 
 
 2.Press “W” into Real Life Order
 

 3. move your mouse change music speed and image
 

 Also, provide TouchOSC
 
 Audio
 - Audio Sample damaged-corrupted
 - Audio Sample nej-nej-dry
 - Audio Sample metallic-noises-on-tape
 - Audio Sample rack
 - Audio Sample horror-4-alien
 
 Source of Code example
 - Mike, Maximilian openFrameworksExamples  Maxim Granular0_92
          http://www.maximilian.strangeloop.co.uk
 */
#include "ofApp.h"

//#include "maximilian.h"/* include the lib */
#include "time.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /* This is stuff you always need.*/
    
    sender.setup(HOST, SENDPORT);
    receiver.setup(RECEIVEPORT);
    
    //load samples
    //samples from http://freesound.org
    sound.load(ofToDataPath("toiletrolltube__damaged-corrupted.wav"));
    sound2.load(ofToDataPath("roses1401__nej-nej-dry.wav"));
    sound3.load(ofToDataPath("455430__uzbazur__metallic-noises-on-tape.wav"));
    sound4.load(ofToDataPath("gis-sweden__electronic-minute-no-211-not-that-entropical-after-all-vcv-rack.wav"));
    sound5.load(ofToDataPath("neolein__horror-4-alien.wav"));
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(255);
    ofSetFrameRate(200);
    
    sampleRate     = 44100; /* Sampling Rate */
    bufferSize    = 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    

    ts = new maxiTimePitchStretch<grainPlayerWin, maxiSample>(&sound);
    ts2 = new maxiTimePitchStretch<grainPlayerWin, maxiSample>(&sound2);
    ts3 = new maxiTimePitchStretch<grainPlayerWin, maxiSample>(&sound3);
    ts4 = new maxiTimePitchStretch<grainPlayerWin, maxiSample>(&sound4);
    ts5 = new maxiTimePitchStretch<grainPlayerWin, maxiSample>(&sound5);
    
    stretches.push_back(ts);
    stretches.push_back(ts2);
    stretches.push_back(ts3);
    stretches.push_back(ts4);
    stretches.push_back(ts5);
    speed = 1;
    length = 0.005;
    current=0;
    
    //fft.setup(2048, 1024, 512);
    fft.setup(1024, 512, 256);
    oct.setup(44100, 1024, 10);
    
    int current = 0;
    ofxMaxiSettings::setup(sampleRate, 0.5, initialBufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    
    mouseMove=true;

    //ofBackground(0,0,0);
    
    //switches on the DAC
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 5); /* this has to happen at the end of setup - it switches on the DAC */
    // set phase here
    phase = 0;
    ofSetRectMode(OF_RECTMODE_CENTER);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //WEKINATOR
    if (!mouseMove) {
        
        
        while(receiver.hasWaitingMessages()){
            // get the next message
            ofxOscMessage m;
            receiver.getNextMessage(&m);
        
            // check for mouse moved message
            if(m.getAddress() == "/wek/outputs"){
                
                cout << m.getArgAsFloat(0);
                speed = ((double ) m.getArgAsFloat(0) * 4.0) - 2.0;
                length = (m.getArgAsFloat(1) * 0.1) + 0.001;
                pos = ((double) m.getArgAsFloat(0) * 2.0);
                
            }
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(0,20); // draw a background which can make some shadow
    
    //ofNoFill();
    for(int i=0; i < oct.nAverages; i++) {
        
        ofSetColor(oct.averages[i] / 5.0 * 255.0, oct.averages[i] / 10.0 * 255.0, oct.averages[i] / 15.0 * 255.0,oct.averages[i] / 10.0 * 255.0);
        
        ofDrawRectangle(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
        //    for(int i=0; i < oct.nAverages; i++) {
        //        ofSetColor((30+oct.averages[i] / 30.0 * 255.0),
        //                   (20+oct.averages[i] / 30.0 * 255.0),
        //                   (oct.averages[i] / 30.0 * 255.0),
        //                   (int)(ofGetFrameNum() * 0.5) % 255);
        //        ofSetColor(10 + ((int)(ofGetFrameNum() * 0.5) % 255),
        //                   10 + ((int)(ofGetFrameNum() * 0.5) % 255),
        //                   0,
        //                   oct.averages[i] / 10.0 * 255.0);
        
        
        
        ofSetColor((10+(int)(ofGetFrameNum() * 0.8) % 255),
                   (10+(int)(ofGetFrameNum() * 0.5) % 255),
                   ((int)(ofGetFrameNum() * 0.5) % 255),
                   oct.averages[i] / 5.0 * 255.0);  // set color accounding to different sounds
        
        glPushMatrix();
        ofPushStyle();
        ofSetLineWidth(i/5);
        ofSetCircleResolution(200);
        //
        //ofSetSphereResolution(200);
        glTranslatef(ofGetWidth()/2,ofGetHeight()/2, 0);
        glRotatef(0.01 * ofGetFrameNum() * speed * i, 0.01 * ofGetFrameNum() * speed * i,0.01 * ofGetFrameNum() * speed * i, 0);
        
        // here draw my shape
        
        ofRotateXDeg(i*5);
        float defaultAngle = ofMap(mouseX, 0, ofGetWidth(), -PI/12, PI/12);
        float tabAngle = ofMap(mouseY,0,ofGetHeight(),-1.5*PI, 1.5*PI);
        float deltaTheta = 1;
        float friction = .6;
        float maxRot = PI / 10;
        float thetaSpeed = (static_cast<void>((deltaTheta + defaultAngle) * friction), -maxRot, maxRot);
        tabAngle += thetaSpeed;
        ofRotateYDeg(tabAngle);
        ofRotateZDeg(i);
        //ofDrawBox(0, i*5, i*i, i*3);
        //ofDrawRectangle(i*5, i*5, i*5, i*5);
        //ofDrawLine(0, 0, i*16, i*17);
        
        ofDrawCircle(i*5, i*5, i*10);
        //ofNoFill();
        
        // draw lines
        //            ofRotate(ofRadToDeg(i/2));
        //            float x = sin(ofRadToDeg(i+phase/2)), y = cos(ofRadToDeg(i+phase/2));
        //
        //            float x2 = x * sqrt(1 - pow(x, 2));
        //            float y2 = y * sqrt(1 - pow(y, 2));
        //
        //            float a = ofMap(mouseX, 0, ofGetWidth(), 50, ofGetWidth()/2,true);
        //            float b = ofMap(mouseY, 0, ofGetHeight(), 50, ofGetHeight()/2,true);
        //
        //            float d = ofDist(x*900, y*900, x2*a, y2*mouseY);
        //            float maxD = ofDist(0, 0, 900, 900);
        //            //float e = ofMap(d, 100, 450, 25, .5);
        //            ofColor(0, 250, 250);
        //            ofSetLineWidth(i);
        //            ofLine(x*450, y*450, x2*a, y2*mouseY);
        //            ofSetLineWidth(d*3);
        //            ofSetColor(250, 145, 0);
        ofPopStyle();
        glPopMatrix();
    }
}



//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    for (int i = 0; i < bufferSize; i++){
        //make 'wave' equal something noisy
        wave = stretches[current]->play(1.,speed, length, 4, 0);
        
        if (fft.process(wave)) {
            oct.calculate(fft.magnitudes);
        }
        //play result
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0]; //left channel
        output[i*nChannels + 1] = outputs[1]; //right channel
        
    }
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // samples are "interleaved"
    for(int i = 0; i < bufferSize; i++){
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (++current > stretches.size()-1) current = 0;
    mouseMove=!mouseMove;
    cout << mouseMove;
    
            if(key=='q'){
                ofNoFill();
             }
            if(key=='w'){
                ofFill();
            }
    //
    //        if(key=='e'){
    //            grainLength = grainLength  +0.001;
    //        }
    //        if(key=='r'){
    //             grainLength = grainLength -0.001;
    //        }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    // here setup My lowpass Filter
    float x1 =  myFilter.lopass(x,0.25);
    float y1 = myFilter2.lopass(y,0.25);
    
    if (mouseMove) {
        speed = ((double ) x1 / ofGetWidth() * 4.0) - 2.0;
        length = ((double) y1 / ofGetHeight() * 0.1) + 0.001;
        if (length < 0.01 ) length = 0.01;
        if (length > 0.4 ) length = 0.4;
        pos = ((double) x1 / ofGetWidth() * 2.0);
        //cout << pos << endl;
        
        ofxOscMessage m;
        m.setAddress("/wekinator/control/outputs");
        m.addFloatArg((float)x/ofGetWidth());
        m.addFloatArg((float)y/ofGetHeight());
        m.addFloatArg((float)current/stretches.size()-1);
        sender.sendMessage(m);
        cout << "messageSent" << "\n";

    }
  
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
