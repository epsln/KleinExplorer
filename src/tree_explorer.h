#pragma once
#ifndef KleinExplorer_h
#define KleinExplorer_h

#include <cmath>
#include <complex>
#include <vector>

#include "Mobius.h"

class KleinExplorer{
	int start_tag;
	int start_state;

	int level = 0;
	float epsilon;
	int max_depth;
	vector<int> tag;
	vector<int> state;
	vector<vector<int>> FSA;

	vector<MobiusT> words;
	vector<MobiusT> generators;
	vector<vector<complex<float>>> fixedPoints;
	MobiusT start_word;

	public:
		KleinExplorer(int max_d);
		void set_next_state(int idx_gen);
		int get_next_state(int idx_gen);
		int get_right_gen();
		int get_left_gen();
		int branch_terminated();
		void backward_move();
		int available_turn();
		void turn_forward_move();
		void forward_move();
		void compute();
};

#endif
