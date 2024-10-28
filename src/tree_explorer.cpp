#include <complex>
#include <cmath>

#include "tree_explorer.h"
#include "Mobius.h"
#include "math_utils.h"

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

	int i = 0 ;
	float o = 0;
	for (int i = 0; i < fixedPoints[idx_gen].size() - 1; i++){
		fp = fixedPoints[idx_gen][i];
		comp_fp = fixedPoints[idx_gen][i + 1];

		p = words[level].apply(fp);
		comp_p = words[level].apply(comp_fp);
		o += abs(p - comp_p);
		if (abs(p - comp_p) > epsilon)
			return 0;
	}

	for (int i = 0; i < fixedPoints[idx_gen].size() - 1; i++){
		fp = fixedPoints[idx_gen][i];
		comp_fp = fixedPoints[idx_gen][i + 1];
		p = words[level].apply(fp);
		comp_p = words[level].apply(comp_fp);

		//TODO: Implement me
		//line(p, comp_p, img);
	}

	return 1;
}

void KleinExplorer::backward_move(){
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
	int idx_gen = get_right_gen();

	set_next_state(idx_gen);

	tag[level + 1] = idx_gen;

	if (level == -1)
		words[0] = generators[idx_gen];
	else
		words[level] = words[level - 1].compose(generators[idx_gen]);
	level += 1;
}

void KleinExplorer::compute(){
	tag[0] = start_tag;
	words[0] = start_word ;
	state[0] = start_state ;

	while (!level == -1 || !tag[0] == start_tag){
		while (branch_terminated()){

			forward_move();

			do	
				backward_move();
			while(available_turn() == 1 or level == -1);

			if (level == -1 and tag[0] == start_tag)
				break;

			turn_forward_move();

		}
	}
}

KleinExplorer::KleinExplorer(int max_d){
	max_depth = max_d;
}
