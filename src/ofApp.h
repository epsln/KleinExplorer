#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "tree_explorer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
		ofxFloatSlider ta_real;
		ofxFloatSlider ta_imag;
		ofxFloatSlider tb_real;
		ofxFloatSlider tb_imag;
		ofxIntField max_depth;
		ofxFloatField epsilon;
		ofxButton saveImg;
		ofxButton computeImg;

		ofxPanel parametersPanel;
		
		ofImage img;
		
		complex<float> ta, tb;
		MobiusT generators[4];
		Fraction spe_fract;
		KleinFractalModel kfm;
		KleinExplorer ke;

		complex<float> center = 0;;
		float zoom = 1;

		//  MARK: - ofBaseApp interface boilerplate:
		//  void update() override;
		void keyPressed(int key) override;
		//	void keyReleased(int key) override;
		//	void mouseMoved(int x, int y ) override;
		//	void mouseDragged(int x, int y, int button) override;
		//	void mousePressed(int x, int y, int button) override;
		//	void mouseReleased(int x, int y, int button) override;
		//	void mouseEntered(int x, int y) override;
		//	void mouseExited(int x, int y) override;
		//	void windowResized(int w, int h) override;
		//	void dragEvent(ofDragInfo dragInfo) override;
		//	void gotMessage(ofMessage msg) override;

};
