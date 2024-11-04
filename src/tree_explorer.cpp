#include <complex>
#include <cstring>
#include <cmath>
#include "ofMain.h"

#include "tree_explorer.h"
#include "Mobius.h"
#include "math_utils.h"
#include "klein_fractal_model.h"

using namespace std;

void KleinExplorer::set_next_state(int idx_gen){
	state[level + 1] = FSA[state[level]][idx_gen];
}

int KleinExplorer::get_next_state(int idx_gen){
	return FSA[state[level]][idx_gen];
}

int KleinExplorer::get_right_gen(){
	int idx_gen = 0;
	int i = 1;
	do{
		idx_gen = (tag[level] + i) % 4;
		i += 1;
	}while(get_next_state(idx_gen) == 0);

	return idx_gen;
}

int KleinExplorer::get_left_gen(){
	int idx_gen = 0;
	int i = 1;
	do{
		idx_gen = mod(tag[level + 1] - i, 4);
		i += 1;
	}while(get_next_state(idx_gen) == 0);

	return idx_gen;
}

int KleinExplorer::branch_terminated(){
	if (level == max_depth - 1)
		return 1;

	int idx_gen = tag[level];

	complex<float> p;
	complex<float> fp;
	complex<float> comp_p;
	complex<float> comp_fp;

	float o = 0;
	ofLog(OF_LOG_NOTICE, "Branch termination @ level: %d", level) ;
	for (int i = 0; i < fixedPoints[idx_gen].size() - 1; i++){
		fp = fixedPoints[idx_gen][i];
		comp_fp = fixedPoints[idx_gen][i + 1];

		p = words[level].apply(fp);
		comp_p = words[level].apply(comp_fp);
		o += abs(p - comp_p);
		ofLog(OF_LOG_NOTICE, "p0: %f %f, p1: %f %f, abs: %f", real(p), imag(p), real(comp_p), imag(comp_p), abs(p - comp_p)); 

		if (abs(p - comp_p) > epsilon)
			return 0;
	}

	for (int i = 0; i < fixedPoints[idx_gen].size() - 1; i++){
		fp = fixedPoints[idx_gen][i];
		comp_fp = fixedPoints[idx_gen][i + 1];
		p = words[level].apply(fp);
		comp_p = words[level].apply(comp_fp);

		//TODO: Implement me (using of methods)
		float x0 = ofMap(real(p), -1, 1, 0, 1080);
		float y0 = ofMap(imag(p), -1, 1, 0, 1080);
		float x1 = ofMap(real(comp_p), -1, 1, 0, 1080);
		float y1 = ofMap(imag(comp_p), -1, 1, 0, 1080);
		ofSetColor(225);
		ofSetLineWidth(1);
		ofLog(OF_LOG_NOTICE, "Point %d %d", x0, y0); 
		ofDrawLine(x0, y0, x1, y1);
	}

	return 1;
}

void KleinExplorer::backward_move(){
	ofLog(OF_LOG_NOTICE, "Backward move @ level: %d", level) ;
	level -= 1;
}

int KleinExplorer::available_turn(){
	int idx_gen = get_right_gen();
	if (level == -1)
		return 1;

	if (FSA[state[level + 1]][idx_gen] == 0)
		return 0;
	else
		return 1;
}

void KleinExplorer::turn_forward_move(){
	ofLog(OF_LOG_NOTICE, "Turn Forward move @ level: %d", level) ;
	int idx_gen = get_left_gen();

	set_next_state(idx_gen);
	tag[level + 1] = idx_gen;

	if (level == -1)
		words[0] = generators[idx_gen];
	else
		words[level] = words[level - 1].compose(generators[idx_gen]);

	level += 1;
}

void KleinExplorer::forward_move(){
	ofLog(OF_LOG_NOTICE, "Forward move @ level: %d", level) ;
	int idx_gen = get_right_gen();

	set_next_state(idx_gen);

	tag[level + 1] = idx_gen;

	words[level].print();
	if (level == -1)
		words[0] = generators[idx_gen];
	else
		words[level] = words[level - 1].compose(generators[idx_gen]);
	level += 1;
}

void KleinExplorer::compute(){
	tag[0] = 0;
	words[0] = generators[0];
	state[0] = 1;

	ofLog(OF_LOG_NOTICE, "Compute @ level %d", level); 
	while (!(level == -1 && tag[0] == start_tag)){
		while (branch_terminated())
			forward_move();

		do	
			backward_move();
		while(available_turn() != 1 || level != -1);

		if (level == -1 && tag[0] == start_tag)
			break;

		turn_forward_move();

	}
}

KleinExplorer::KleinExplorer(int max_d, float eps, KleinFractalModel kfm){
	max_depth = max_d;
	epsilon = eps; 
	memcpy(generators, kfm.generators, sizeof(MobiusT) * 4);
	fixedPoints = kfm.fixedPoints;
	tag.reserve(max_d);
	state.reserve(max_d);
	words.reserve(max_d);
	fill(tag.begin(), tag.end(), 0);//Probably will screw things up
	fill(state.begin(), state.end(), 0);

	MobiusT defaultWord = MobiusT(0,0,0,0);
	fill(words.begin(), words.end(), defaultWord);
}
