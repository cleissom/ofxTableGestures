#include "testApp.h"

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "LongPushFeedback.hpp"



#include "InputGestureDirectFingers.hpp"
#include "FigureGraphic.hpp"
#include "Alarm.hpp"

class Test2 : public EventClient {
	// pdsp modules
	pdsp::Engine            engine;
	pdsp::VAOscillator      osc;
	pdsp::LFO               lfo;
	pdsp::ValueControl      pitch_ctrl;

public:
	Test2() {
		this->registerEvent(InputGestureDirectObjects::Instance().updateObject, &Test2::changePitch, this);

		pitch_ctrl >> osc.in_pitch();
		osc.out_sine() * dB(-12.0f) >> engine.audio_out(0); // connect to left output channel
		osc.out_sine() * dB(-12.0f) >> engine.audio_out(1); // connect to right right channel

		pitch_ctrl.set(36.0f);

		//engine.listDevices();
		engine.setDeviceID(1); // REMEMBER TO SET THIS AT THE RIGHT INDEX!!!!

		// start your audio engine !
		engine.setup(44100, 512, 3);
	}

	void changePitch(InputGestureDirectObjects::enterObjectArgs & e) {
		cout << e.object->s_id << endl;
		float pitch = ofMap(e.object->angle, 0, M_2PI, 36.0f, 72.0f);
		pitch_ctrl.set(pitch);
	}
};



class Test: public Graphic
{
    Figures::Polygon polygon;
    FigureGraphic * fg;
    float time_circle;
    public:
    Test()
    {
        polygon.AddVertex(ofPoint(-0.05f, -0.05f));
        polygon.AddVertex(ofPoint(-0.05f, 0.05f));
        polygon.AddVertex(ofPoint(0.05f, 0.05f));
        polygon.AddVertex(ofPoint(0.05f, 0.025f));
        polygon.AddVertex(ofPoint(-0.025f, 0.025f));
        polygon.AddVertex(ofPoint(-0.025f, -0.025f));
        polygon.AddVertex(ofPoint(0.025f, -0.025f));
        polygon.AddVertex(ofPoint(0.025f, 0.0f));
        polygon.AddVertex(ofPoint(0.05f, 0.0f));
        polygon.AddVertex(ofPoint(0.05f, -0.05f));

        //polygon.SetTexture("temp.png");
        
        fg = new FigureGraphic(&polygon);
        fg->transformation.setTranslation(ofRandom(0,1),ofRandom(0,1),0);
        fg->transformation.glRotate(ofRandom(0,360),0,0,1);
        //registerEvent(InputGestureBasicFingers::Instance().enterTuioCursor, &Test2::genericCallback);
        fg->registerMyEvent(InputGestureDirectFingers::Instance().enterCursor, &Test::enter,this);
        //fg->registerMyEvent(InputGestureDirectFingers::Instance().exitCursor, &Test2::genericCallback2,this);
        
        time_circle = ofRandom(0.1,2);
        
        fg->color.r = ofRandom(0,255);
        fg->color.g = ofRandom(0,255);
        fg->color.b = ofRandom(0,255);
        fg->color.a = 100;
        fg->isHidden(true);
    }
	
    void enter(InputGestureDirectFingers::enterCursorArgs & e)
    {
        fg->isHidden(false);
        fg->hasAlpha(true);
        //fg->canCollide(false);
        fg->setFill(false);
        Alarm::Cancel(this);
        Alarm::Setup(ofGetElapsedTimef()+4,this,&Test::alive);
    }
    void alive(float & t)
    {
        fg->hasAlpha(false);
        fg->canCollide(true);
        fg->setFill(true);
        fg->color.r = ofRandom(0,255);
        fg->color.g = ofRandom(0,255);
        fg->color.b = ofRandom(0,255);
        Alarm::Setup(ofGetElapsedTimef()+4,this,&Test::die);
    }
    
    void die(float & t)
    {
        fg->isHidden(true);
        fg->canCollide(true);
    }
    
    void update()
    {
        fg->transformation.glRotate(1,0,0,1);
    }
};

void testApp::pitch(float arg) {
	
}
//--------------------------------------------------------------
void testApp::setup(){

    tableapp.setup();

    for (int i = 0; i < 500; ++i)
        new Test();
    new CursorFeedback();
    new FigureFeedback();
    new TapFeedback();
    new LongPushFeedback();
	new Test2();

	
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    tableapp.draw();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

