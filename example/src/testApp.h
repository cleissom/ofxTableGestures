#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "TableApp.hpp"
#include "Figure.h"
#include "CollisionHelper.h"
#include "Polygon.h"
#include "ofxPDSP.h"

#include "FigureGraphic.hpp"
#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"
#include "Alarm.hpp"

class TableObject : public pdsp::Patchable, public Graphic {
private:

public:
	DirectObject* object;

	TableObject() {

	}
};

class Generator : public TableObject {

public:

	Generator(int id = 0): id(id) {
		patch();
		registerEvent(InputGestureDirectFingers::I().enterCursor, &Generator::addCursor, this);
		registerEvent(InputGestureDirectObjects::I().updateObject, &Generator::updateObject, this);
	} // default constructor
	Generator(const Generator & other) { patch(); } // you need this to use std::vector with your class, otherwise will not compile
	// remember that is a bad thing to copy construct in pdsp, 
	//      always just resize the vector and let the default constructor do the work
	//          resizing the vector will also disconnect everything, so do it just once before patching


	void patch() {

		//create inputs/outputs to be used with the in("tag") and out("tag") methods
		addModuleInput("input", input); // the first input added is the default input
		addModuleOutput("signal", amp); // the first output added is the default output


		//patching
		osc.out_saw() >> amp;
		pitch_ctrl >> osc.in_pitch();
		amp.set(1.0f);
	}

	void addCursor(InputGestureDirectFingers::newCursorArgs & a) {
		cout << "cursor input" << endl;
	}

	void updateObject(InputGestureDirectObjects::updateObjectArgs& a) {
		int id = a.object->f_id;
		if (id == this->id) {
			cout << a.object->angle << endl;
			float pitch = ofMap(a.object->angle, 0, M_2PI, 36.0f, 80.0f);
			pitch_ctrl.set(pitch);
		}
	}

	

private:
	int id;
	pdsp::PatchNode     input;
	pdsp::ValueControl     pitch_ctrl;
	pdsp::Amp           amp;
	pdsp::VAOscillator  osc;
};

class Effects : public TableObject {

public:

	Effects(int id) : id(id) {
		patch();
		registerEvent(InputGestureDirectFingers::I().enterCursor, &Effects::addCursor, this);
		registerEvent(InputGestureDirectObjects::I().updateObject, &Effects::updateObject, this);
	}
	Effects(const Effects  & other) { patch(); } // you need this to use std::vector with your class, otherwise will not compile


	void patch() {

		//create inputs/outputs to be used with the in("tag") and out("tag") methods
		addModuleInput("input", input); // the first input added is the default input
		addModuleOutput("output", amp); // the first output added is the default output


		input >> filter >> amp;
		cutoff_ctrl >> filter.in_cutoff();
		amp.set(1.0f);
	}

	void addCursor(InputGestureDirectFingers::newCursorArgs & a) {
		cout << "cursor input" << endl;
	}

	void updateObject(InputGestureDirectObjects::updateObjectArgs& a) {
		int id = a.object->f_id;
		if (id == this->id) {
			cout << a.object->angle << endl;
			float cutoff = ofMap(a.object->angle, 0, M_2PI, 10.0f, 120.0f);
			cutoff_ctrl.set(cutoff);
		}
	}

private:
	int id;
	pdsp::PatchNode     input;
	pdsp::Amp           amp;
	pdsp::ValueControl	cutoff_ctrl;
	pdsp::VAFilter      filter; // 24dB multimode filter

};

class testApp : public ofBaseApp{

	public:

        TableApp tableapp;
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		// pdsp modules
		pdsp::Engine            engine;
};

#endif
