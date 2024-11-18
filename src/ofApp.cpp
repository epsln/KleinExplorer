#include "ofApp.h"
#include "recipes.h"
#include "Mobius.h"
#include "tree_explorer.h"
#include "accidents.h"

void ofApp::setup(){

	parametersPanel.setup("Klein Explorer v0");
	parametersPanel.add(ta_real.setup("ta real part", 2, -3, 3));
	parametersPanel.add(ta_imag.setup("ta imaginary part", -0, -3, 3));
	parametersPanel.add(tb_real.setup("tb real part", 2, -3, 3));
	parametersPanel.add(tb_imag.setup("tb imaginary part", 0, -3, 3));
	parametersPanel.add(max_depth.setup("Maximum Depth", 100, 2, 3000));
	parametersPanel.add(epsilon.setup("Epsilon", 0.01, 0.0001, 0.01));
	parametersPanel.add(computeImg.setup("Compute !"));
	parametersPanel.add(saveImg.setup("Save Image"));

	const complex<float> i(0.0, 1.0);
	complex<float> ta = (float)ta_real + (float)ta_imag * i;
	complex<float> tb = (float)tb_real + (float)tb_imag * i;
	spe_fract = Fraction(5, 9);

	kfm = getGeneratorsFromFraction(spe_fract);
	ke = KleinExplorer(max_depth, epsilon, kfm);
	img.grabScreen(0,0,ofGetWidth(),ofGetHeight());

}

void ofApp::draw(){
	const complex<float> i(0.0, 1.0);
	ta = (float)ta_real + (float)ta_imag * i;
	tb = (float)tb_real + (float)tb_imag * i;

	grandmaRecipe(ta, tb, generators);

	//kfm = KleinFractalModel(generators, spe_fract);
	spe_fract = Fraction(11, 27);
	kfm = getGeneratorsFromFraction(spe_fract);
	ke.set_klein_model(kfm);
	ke.set_compute_params(max_depth, epsilon);

	if (saveImg)
		img.save("img.jpg");

	if (computeImg){
		ke.compute();
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
	}
	img.draw(0, 0); // draw at upper-left corner position (O px x 0 px) 
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
