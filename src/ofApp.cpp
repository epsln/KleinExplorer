#include "ofApp.h"
#include "recipes.h"
#include "Mobius.h"
#include "tree_explorer.h"
#include "accidents.h"

void ofApp::setup(){
	ofRectangle bounds(-3, -3, 6, 6); 
	menu = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
	menu->add2dPad("ta", bounds);
	menu->add2dPad("tb", bounds);
	menu->addSlider("Maximum Depth", 5, 1000);
	menu->addSlider("Epsilon", 0.001, 0.1);
	menu->addButton("Compute !");
	menu->addButton("Save Image");
	menu->addHeader("Klein Explorer v0");

	const complex<float> i(0.0, 1.0);
	//	complex<float> tb = (float)tb_real + (float)tb_imag * i;
	spe_fract = Fraction(1, 2);

	kfm = getGeneratorsFromFraction(spe_fract);
  ke = KleinExplorer(10, .1, kfm);
	img.grabScreen(0,0,ofGetWidth(),ofGetHeight());

}

void ofApp::draw(){
	img.draw(0, 0);
  menu->onButtonEvent(this, &ofApp::onButtonEvent);
  menu->on2dPadEvent(this, &ofApp::on2dPadEvent);
  menu->onSliderEvent(this, &ofApp::onSliderEvent);
}

void ofApp::keyPressed(int key){
	const complex<float> i(0.0, 1.0);
	if (key == 'w')
		center += i * zoom * (float)0.1;
	if (key == 'a')
		center += 1 * zoom * (float)0.1;
	if (key == 's')
		center -= i * zoom * (float)0.1;
	if (key == 'd')
		center -= 1 * zoom * (float)0.1;
	if (key == 'q')
		zoom -= .1;
	if (key == 'e')
		zoom += .1;

	ke.set_coords(center, zoom);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
	if (e.target->is("compute !")){
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
	else if (e.target->is("save image")){
		img.save("img.jpg");
	}
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e){
	const complex<float> i(0.0, 1.0);
	if (e.target->is("ta"))
		ta = (float)e.x + (float)e.y * i;
	
	if (e.target->is("tb"))
		tb = (float)e.x + (float)e.y * i;

	grandmaRecipe(ta, tb, generators);
	spe_fract = Fraction(1, 2);
	kfm = KleinFractalModel(generators, spe_fract);
	ke.set_klein_model(kfm);
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
	if (e.target->is("Maximum Depth"))
		max_d = e.target->getValue();
	if (e.target->is("epsilon"))
		epsilon = e.target->getValue();
	ke.set_compute_params(max_d, epsilon);
}
