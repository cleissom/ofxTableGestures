#include "testApp.h"

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "LongPushFeedback.hpp"



#include "InputGestureDirectFingers.hpp"
#include "FigureGraphic.hpp"
#include "Alarm.hpp"

class SlideSynth : public pdsp::Patchable {

public:

	SlideSynth() { patch(); } // default constructor
	SlideSynth(const SlideSynth & other) { patch(); } // you need this to use std::vector with your class, otherwise will not compile
	// remember that is a bad thing to copy construct in pdsp, 
	//      always just resize the vector and let the default constructor do the work
	//          resizing the vector will also disconnect everything, so do it just once before patching


	void patch() {

		//create inputs/outputs to be used with the in("tag") and out("tag") methods
		addModuleInput("pitch", osc.in_pitch()); // the first input added is the default input
		addModuleInput("amp", y_ctrl);
		addModuleInput("filter", filter_cutoff);
		addModuleOutput("signal", amp); // the first output added is the default output


		// pdsp::PatchNode is a class that simply route its inputs to its output
		y_ctrl.enableBoundaries(0.0f, 1.0f); // you can clip the input of pdsp::PatchNode
		y_ctrl.set(0.0f); // and you can set its input default value

		//patching
		osc.out_saw() * 2.0f >> drive >> filter >> amp;
		y_ctrl >> amp.in_mod();
		y_ctrl * 60.0f >> filter.in_cutoff();
		filter_cutoff >> filter.in_cutoff();
		0.3f >> filter.in_reso();
	}

	// those are optional
	pdsp::Patchable & in_pitch() {
		return in("pitch");
	}

	pdsp::Patchable & in_amp() {
		return in("amp");
	}

	pdsp::Patchable & out_signal() {
		return out("signal");
	}

private:
	pdsp::PatchNode     filter_cutoff;
	pdsp::PatchNode     y_ctrl;
	pdsp::PatchNode     pitch_ctrl;
	pdsp::Amp           amp;
	pdsp::VAOscillator  osc;
	pdsp::Saturator1    drive; // distort the signal
	pdsp::VAFilter      filter; // 24dB multimode filter

};

class Test2 : public CanDirectObjects<Graphic> {
	// pdsp modules
	pdsp::Engine            engine;
	pdsp::VAOscillator      osc;
	pdsp::LFO               lfo;
	pdsp::ValueControl      pitch_ctrl;
	pdsp::ValueControl      amp_ctrl;
	pdsp::ValueControl      filter_ctrl;
	pdsp::Amp               amp;
	pdsp::ADSR              env;
	pdsp::TriggerControl    gate_ctrl;
	SlideSynth          synth;

	std::vector<SlideSynth> synths;
	std::vector<pdsp::ValueControl>    pitches;
	std::vector<pdsp::LFO>          drift_lfo;
	std::vector <pdsp::ValueControl>               amps;
	std::vector<pdsp::ValueControl>      filters;

public:
	Test2() {

		synths.resize(3);
		pitches.resize(synths.size());
		filters.resize(synths.size());
		amps.resize(synths.size());

		for (size_t i = 0; i < synths.size(); ++i) {

			pitches[i] >> synths[i].in("pitch");
			amps[i] >> synths[i].in_amp();
			filters[i] >> synths[i].in("filter");

			synths[i] >> engine.audio_out(0);
			synths[i] >> engine.audio_out(1);
		}



		/*
		pitch_ctrl >> synth.in("pitch"); // patching with in("tag")
		amp_ctrl >> synth.in_amp(); // patching with custom in_tag()
		synth * dB(-12.0f) >> engine.audio_out(0);
		synth * dB(-12.0f) >> engine.audio_out(1);

		filter_ctrl >> synth.in("filter");

		pitch_ctrl.set(60.0f);
		pitch_ctrl.enableSmoothing(50.0f); // 50ms smoothing
		amp_ctrl.set(0.0f);
		amp_ctrl.enableSmoothing(50.0f); // 50ms smoothing
		*/
		


		//------------SETUPS AND START AUDIO-------------
#ifdef PC
		engine.setDeviceID(1);
#else
		engine.setDeviceID(0);
#endif // PC

		engine.setup(44100, 512, 3);
	}

	void newObject(DirectObject * object) {
		int i = object->f_id;
		float pitch = ofMap(object->getX(), 0, 1.0f, 36.0f, 72.0f);
		pitches[i].set(pitch);
		float amp = ofMap(object->getY(), 0, 1.0f, 1.0f, 0.0f);
		amps[i].set(amp);
		float freq = ofMap(object->angle, 0, M_2PI, 0.0f, 100.0f);
		filters[i].set(freq);
	}

	void updateObject(DirectObject * object) {
		int i = object->f_id;
		float pitch = ofMap(object->getX(), 0, 1.0f, 36.0f, 72.0f);
		pitches[i].set(pitch);
		float amp = ofMap(object->getY(), 0, 1.0f, 1.0f, 0.0f);
		amps[i].set(amp);
		float freq = ofMap(object->angle, 0, M_2PI, 0.0f, 100.0f);
		filters[i].set(freq);

	}

	void removeObject(DirectObject * object) {
		int i = object->f_id;
		amps[i].set(0.0f);
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

