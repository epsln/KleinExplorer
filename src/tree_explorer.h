#ifndef KleinExplorer_h
#define KleinExplorer_h

#include <cmath>
#include <complex>
#include <vector>
#include <array>

#include "Mobius.h"
#include "klein_fractal_model.h"

class KleinExplorer{
	//Used for multiproc
	int start_tag = 0;
	int start_state = 1;
	MobiusT generators[4];
	MobiusT start_word = generators[0]; //TODO implement this for multiproc
	int level = 0;
	float epsilon;
	int max_depth;

	vector<int> tag;
	vector<int> state;

	//Default FSA for now
	int FSA[5][4] = {{1, 2, 3, 4}, {1, 2, 0, 4}, {1, 2, 3, 0}, {0, 2, 3, 4}, {1, 0, 3, 4}};
	vector<MobiusT> words;
	vector<vector<complex<float>>> fixedPoints;

	float viewbox_xmin = -1;
	float viewbox_xmax =  1;
	float viewbox_ymin = -1;
	float viewbox_ymax =  1;

	public:
		KleinExplorer();
		KleinExplorer(int max_d, float epsilon, KleinFractalModel kfm);
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
		void print_word();
		void set_klein_model(KleinFractalModel kfm);
		void set_compute_params(int max_d, float epsilon);
		void set_coords(complex<float> center, float zoom);
};

#endif
