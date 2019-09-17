#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "TableApp.hpp"
#include "Figure.h"
#include "CollisionHelper.h"
#include "Polygon.h"
#include "ofxPDSP.h"

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

		void pitch(float arg);

		// pdsp modules
		pdsp::Engine            engine;
		pdsp::VAOscillator      osc;
		pdsp::LFO               lfo;
		pdsp::ValueControl      pitch_ctrl;
};

#endif
