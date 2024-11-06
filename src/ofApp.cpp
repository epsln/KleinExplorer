#include "ofApp.h"
#include "recipes.h"
#include "Mobius.h"
#include "tree_explorer.h"

void ofApp::setup(){

	parametersPanel.setup("Klein Explorer v0");
	parametersPanel.add(ta_real.setup("ta real part", 2, -3, 3));
	parametersPanel.add(ta_imag.setup("ta imaginary part", -0, -3, 3));
	parametersPanel.add(tb_real.setup("tb real part", 2, -3, 3));
	parametersPanel.add(tb_imag.setup("tb imaginary part", 0, -3, 3));
	parametersPanel.add(max_depth.setup("Maximum Depth", 10, 2, 3000));
	parametersPanel.add(epsilon.setup("Epsilon", 0.1, 0.0001, 0.01));

	const complex<float> i(0.0, 1.0);
	complex<float> ta = (float)ta_real + (float)ta_imag * i;
	complex<float> tb = (float)tb_real + (float)tb_imag * i;
	generators[4];
	grandmaRecipe(ta, tb, generators);
	spe_fract = Fraction(1, 2);

	kfm = KleinFractalModel(generators, spe_fract);
	ke = KleinExplorer(max_depth, epsilon, kfm);
}

void ofApp::draw(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	const complex<float> i(0.0, 1.0);
	ta = (float)ta_real + (float)ta_imag * i;
	tb = (float)tb_real + (float)tb_imag * i;

	grandmaRecipe(ta, tb, generators);

	kfm = KleinFractalModel(generators, spe_fract);
	ke.set_klein_model(kfm);
	ke.compute();
	parametersPanel.draw();
}
