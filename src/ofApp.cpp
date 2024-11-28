#include "ofApp.h"
#include "recipes.h"
#include "Mobius.h"
#include "tree_explorer.h"
#include "accidents.h"

void ofApp::setup(){
	ofRectangle bounds(-3, -3, 6, 6); 
	menu = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );

  grandma_folder = menu -> addFolder("Grandma Recipe", ofColor::white); 
	grandma_folder->addSlider("ta (real part)", -3, 3);
	grandma_folder->addSlider("ta (imag part)", -3, 3);
	grandma_folder->addSlider("tb (real part)", -3, 3);
	grandma_folder->addSlider("tb (imag part)", -3, 3);
	grandma_folder->addButton("Compute !");
  grandma_folder->onButtonEvent(this, &ofApp::onButtonEvent);
  grandma_folder->onSliderEvent(this, &ofApp::onSliderEvent);
	
  grandma_special_folder = menu -> addFolder("Grandma Special Recipe", ofColor::white); 
	grandma_special_folder->addSlider("ta (real part)", -3, 3);
	grandma_special_folder->addSlider("ta (imag part)", -3, 3);
	grandma_special_folder->addSlider("tb (real part)", -3, 3);
	grandma_special_folder->addSlider("tb (imag part)", -3, 3);
	grandma_special_folder->addSlider("taB (real part)", -3, 3);
	grandma_special_folder->addSlider("taB (imag part)", -3, 3);
	grandma_special_folder->addButton("Compute !");
  grandma_special_folder->onButtonEvent(this, &ofApp::onButtonEvent);
  grandma_special_folder->onSliderEvent(this, &ofApp::onSliderEvent);

  maskit_folder = menu -> addFolder("Maskit Recipe", ofColor::white); 
	maskit_folder->addSlider("ta (real part)", -3, 3);
	maskit_folder->addSlider("ta (imag part)", -3, 3);
	maskit_folder->addButton("Compute !");
  maskit_folder->onButtonEvent(this, &ofApp::onButtonEvent);
  maskit_folder->onSliderEvent(this, &ofApp::onSliderEvent);

  jorgensen_folder = menu -> addFolder("Jorgensen Recipe", ofColor::white); 
	jorgensen_folder->addSlider("ta (real part)", -3, 3);
	jorgensen_folder->addSlider("ta (imag part)", -3, 3);
	jorgensen_folder->addSlider("tb (real part)", -3, 3);
	jorgensen_folder->addButton("Compute !");
  jorgensen_folder->onButtonEvent(this, &ofApp::onButtonEvent);
  jorgensen_folder->onSliderEvent(this, &ofApp::onSliderEvent);

	menu -> addSlider("Maximum Depth", 5, 1000);
	menu -> addSlider("Epsilon", 0.001, 0.1);
	menu ->addButton("Save Image");
	grandma_folder->expand();


	const complex<float> i(0.0, 1.0);
	spe_fract = Fraction(1, 2);

	kfm = getGeneratorsFromFraction(spe_fract);
  ke = KleinExplorer(10, .1, kfm);
	img.grabScreen(0,0,ofGetWidth(),ofGetHeight());

}

void ofApp::update(){
	grandma_folder -> update();
}
void ofApp::draw(){
	img.draw(0, 0);
	grandma_folder -> draw();
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
	if (e.target == menu -> getButton("compute !", "grandma recipe")){
		grandmaRecipe(ta, tb, generators);
		spe_fract = Fraction(1, 2);
		kfm = KleinFractalModel(generators, spe_fract);
		ke.set_klein_model(kfm);
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
	if (e.target == menu -> getButton("compute !", "grandma special recipe")){
		grandmaSpecialRecipe(ta, tb, tab, generators);
		spe_fract = Fraction(1, 2);
		kfm = KleinFractalModel(generators, spe_fract);
		ke.set_klein_model(kfm);
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
	if (e.target == menu -> getButton("compute !", "maskit recipe")){
		maskitRecipe(ta, generators);
		spe_fract = Fraction(1, 2);
		kfm = KleinFractalModel(generators, spe_fract);
		ke.set_klein_model(kfm);
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
	if (e.target == menu -> getButton("compute !", "jorgensen recipe")){
		jorgensen(ta, tb, generators);
		spe_fract = Fraction(1, 2);
		kfm = KleinFractalModel(generators, spe_fract);
		ke.set_klein_model(kfm);
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

	if (e.target->is("tab"))
		tab = (float)e.x + (float)e.y * i;

}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
	const complex<float> i(0.0, 1.0);
	if (e.target->is("Maximum Depth"))
		max_d = e.target->getValue();
	if (e.target->is("epsilon"))
		epsilon = e.target->getValue();
	if (e.target->is("ta (real part)"))
		ta = e.target->getValue() + i * imag(ta);
	if (e.target->is("ta (imag part)"))
		ta = e.target->getValue() * i + real(ta);
	if (e.target->is("tb (real part)"))
		tb = e.target->getValue() + i * imag(ta);
	if (e.target->is("tb (imag part)"))
		tb = e.target->getValue() * i + real(ta);

	ke.set_compute_params(max_d, epsilon);
}
