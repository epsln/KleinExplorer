#include "ofApp.h"
#include "recipes.h"
#include "Mobius.h"
#include "tree_explorer.h"

void ofApp::setup(){

	parametersPanel.setup("Klein Explorer v0");
	parametersPanel.add(ta_real.setup("ta real part", 2, -3, 3));
	parametersPanel.add(ta_imag.setup("ta imaginary part", 0, -3, 3));
	parametersPanel.add(tb_real.setup("tb real part", 2, -3, 3));
	parametersPanel.add(tb_imag.setup("tb imaginary part", 0, -3, 3));
	parametersPanel.add(max_depth.setup("Maximum Depth", 13, 2, 300));
	parametersPanel.add(epsilon.setup("Epsilon", 0.01, 0.001, 0.1));
}

void ofApp::draw(){
	parametersPanel.draw();
	const complex<float> i(0.0, 1.0);
	complex<float> ta = (float)ta_real + (float)ta_imag * i;
	complex<float> tb = (float)tb_real + (float)tb_imag * i;
	MobiusT generators[4];
	grandmaRecipe(ta, tb, generators);
	Fraction spe_fract = Fraction(1, 2);
	KleinFractalModel kfm = KleinFractalModel(generators, spe_fract);
	KleinExplorer ke = KleinExplorer(max_depth, epsilon, kfm);
	ke.compute();
}
