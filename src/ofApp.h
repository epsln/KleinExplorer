#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

#include "tree_explorer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
    ofxDatGui* menu;
		
		ofImage img;
		
		complex<float> ta, tb;
		MobiusT generators[4];
		Fraction spe_fract;
		KleinFractalModel kfm;
		KleinExplorer ke;

		complex<float> center = 0;;
		float zoom = 1;

		int max_d = 10;
		float epsilon = .1;

		void keyPressed(int key) override;
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void on2dPadEvent(ofxDatGui2dPadEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
};

