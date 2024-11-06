#include "klein_fractal_model.h"
#include "math_utils.h"
#include <vector>
#include <cstring>
#include <algorithm>
#include "ofMain.h"

using namespace std;

KleinFractalModel::KleinFractalModel(){}

KleinFractalModel::KleinFractalModel(MobiusT gen[4], Fraction spe_fract): special_fract(spe_fract){
	memcpy(generators, gen, sizeof(MobiusT) * 4);
	compute_fixed_points();
	
}

void KleinFractalModel::compute_fixed_points(){
	// See pp. 276
	int num = 1;
	int c = special_fract.q;
	vector<int> special_word, special_word_inv;
	int gen;
	do{
		if (num + special_fract.q > special_fract.p + special_fract.q){
			c = -special_fract.p;
			gen = 0;
		}

		else if (num - special_fract.p < 1){
			c = special_fract.q;
			gen = 3;
		}

		num += c;
		special_word.push_back(gen);
	}while(num != 1);
	reverse(special_word.begin(), special_word.end());

	for (int i = 0; i < special_word.size(); i++){
		special_word_inv.push_back((i + 2) % 4);
	}

	vector<vector<int>> special_words;

	vector<complex<float>> fp;
	//Couldn't find a better way to init 
	fixedPoints.push_back(vector<complex<float>> {0});
	fixedPoints.push_back(vector<complex<float>> {0});
	fixedPoints.push_back(vector<complex<float>> {0});
	fixedPoints.push_back(vector<complex<float>> {0});
	
	special_words.push_back({0, 1, 2, 3});
	special_words.push_back(special_word);
	special_words.push_back(special_word_inv);
	special_words.push_back({1, 0, 3, 2});

	int idx_gen;

	for (auto word: special_words){
		for (int i = 0; i < word.size(); i++){
			vector<int> perm;
			cyclic_permutation(word, perm, -i);
			MobiusT m = generators[perm[0]];
			for (int j = 1; j < perm.size(); j++){
				m = m.compose(generators[perm[j]]);
			}
			m.print();

			idx_gen = perm.back();
			fixedPoints[idx_gen].push_back(m.compute_fixed_points());
		}
	}
	for (int i = 0; i < 4; i++){
		fixedPoints[i].erase(fixedPoints[i].begin());
	}
}

