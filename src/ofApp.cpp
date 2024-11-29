#include <string> 
#include "ofApp.h"
#include "recipes.h"
#include "Mobius.h"
#include "tree_explorer.h"
#include "accidents.h"

void ofApp::setup(){
	menu = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );

	vector<string> recipes = {"Grandma Recipe", "Grandma Special Recipe",  "Maskit Recipe", "Jorgensen Recipe"};
	menu -> addDropdown("Recipe", recipes) -> select(0); 

	menu -> addSlider("ta (real part)", -3, 3, 2);
	menu -> addSlider("ta (imag part)", -3, 3, 0);
	menu -> addSlider("tb (real part)", -3, 3, 2);
	menu -> addSlider("tb (imag part)", -3, 3, 0);
	menu -> addSlider("taB (real part)", -3, 3) -> setVisible(false);
	menu -> addSlider("taB (imag part)", -3, 3) -> setVisible(false);

	menu -> addTextInput("Special Fraction Numerator", "1");
	menu -> addTextInput("Special Fraction Denominator", "1");
	menu -> addSlider("Maximum Depth", 5, 1000, max_d);
	menu -> addSlider("Epsilon", 0.001, 0.1, epsilon);
	menu -> addToggle("Real Time Mode");
	menu -> addButton("Save Image");
	menu -> addButton("Compute !");

	menu -> onSliderEvent(this, &ofApp::onSliderEvent);
	menu -> onButtonEvent(this, &ofApp::onButtonEvent);
	menu -> onToggleEvent(this, &ofApp::onToggleEvent);
	menu -> onDropdownEvent(this, &ofApp::onDropdownEvent);
	menu -> onTextInputEvent(this, &ofApp::onTextInputEvent);


	const complex<float> i(0.0, 1.0);
	spe_fract = Fraction(1, 1);

	//kfm = getGeneratorsFromFraction(spe_fract);
	ke = KleinExplorer(10, .1, kfm);
	img.grabScreen(0,0,ofGetWidth(),ofGetHeight());

}

void ofApp::draw(){
	img.draw(0, 0);
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

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e){
	realTimeMode = e.checked;
	menu -> getButton("compute !") -> setVisible(!e.checked);
}

bool isNumber(const std::string &s) {
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e){
	if (e.target -> is("special fraction numerator") || e.target -> is("special fraction denominator")){
		if (isNumber(e.text)){
			int num = stoi(menu -> getTextInput("special fraction numerator") -> getText());
			int den = stoi(menu -> getTextInput("special fraction denominator") -> getText());
			spe_fract = Fraction(num, den);
		}
		else{
			ofLog(OF_LOG_WARNING, "Invalid input, must be a number");
			e.target -> setText("1");
		}
	}
	if (realTimeMode){
		kfm = KleinFractalModel(generators, spe_fract);
		ke.set_klein_model(kfm);
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
	if (e.target -> is("compute !")){
		kfm = KleinFractalModel(generators, spe_fract);
		ke.set_klein_model(kfm);
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
	else if (e.target->is("save image")){
		img.save("img.jpg");
	}
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e){
	currentRecipeIndex = e.child;
	switch(currentRecipeIndex){
		case 0:
			menu -> getSlider("tb (real part)") -> setVisible(true);
			menu -> getSlider("tb (imag part)") -> setVisible(true);
			menu -> getSlider("tab (real part)") -> setVisible(false);
			menu -> getSlider("tab (imag part)") -> setVisible(false);
			break;
		case 1:
			menu -> getSlider("tb (real part)") -> setVisible(true);
			menu -> getSlider("tb (imag part)") -> setVisible(true);
			menu -> getSlider("tab (real part)") -> setVisible(true);
			menu -> getSlider("tab (imag part)") -> setVisible(true);
			break;
		case 2:
			menu -> getSlider("tb (real part)") -> setVisible(false);
			menu -> getSlider("tb (imag part)") -> setVisible(false);
			menu -> getSlider("tab (real part)") -> setVisible(false);
			menu -> getSlider("tab (imag part)") -> setVisible(false);
			break;
		case 3:
			menu -> getSlider("tb (real part)") -> setVisible(true);
			menu -> getSlider("tb (imag part)") -> setVisible(true);
			menu -> getSlider("tab (real part)") -> setVisible(false);
			menu -> getSlider("tab (imag part)") -> setVisible(false);
			break;
	}
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
	if (e.target->is("tab (real part)"))
		tab = e.target->getValue() + i * imag(ta);
	if (e.target->is("tab (imag part)"))
		tab = e.target->getValue() * i + real(ta);

	ke.set_compute_params(max_d, epsilon);
	switch(currentRecipeIndex){
		case 0:
			grandmaRecipe(ta, tb, generators);
			break;
		case 1:
			grandmaSpecialRecipe(ta, tb, tab, generators);
			break;
		case 2:
			jorgensen(ta, tb, generators);
			break;
		case 3:
			maskitRecipe(ta, generators);
			break;
	}

	if (realTimeMode){
		kfm = KleinFractalModel(generators, spe_fract);
		ke.set_klein_model(kfm);
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
}
