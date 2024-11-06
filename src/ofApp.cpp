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
	parametersPanel.add(saveImg.setup("Save Image"));

	const complex<float> i(0.0, 1.0);
	complex<float> ta = (float)ta_real + (float)ta_imag * i;
	complex<float> tb = (float)tb_real + (float)tb_imag * i;
	grandmaRecipe(ta, tb, generators);
	spe_fract = Fraction(1, 2);

	kfm = KleinFractalModel(generators, spe_fract);
	ke = KleinExplorer(max_depth, epsilon, kfm);

}

void ofApp::draw(){
	const complex<float> i(0.0, 1.0);
	ta = (float)ta_real + (float)ta_imag * i;
	tb = (float)tb_real + (float)tb_imag * i;

	grandmaRecipe(ta, tb, generators);

	kfm = KleinFractalModel(generators, spe_fract);
	ke.set_klein_model(kfm);
	ke.set_compute_params(max_depth, epsilon);
	ke.compute();
	if (saveImg){
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
		img.save("img.jpg");
	}
	parametersPanel.draw();
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
