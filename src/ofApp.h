#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

#include "tree_explorer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
    ofxDatGui* menu;
    ofxDatGuiFolder* grandma_folder, *grandma_special_folder, *maskit_folder, *jorgensen_folder;
		
		ofImage img;

		int currentRecipeIndex = 0;
		
		complex<float> ta, tb, tab;
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
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
};

