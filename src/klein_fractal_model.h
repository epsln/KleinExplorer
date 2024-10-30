#ifndef KleinFractalModel_h
#define KleinFractalModel_h
#include <vector>

#include "fraction.h"
#include "Mobius.h"

using namespace std;

class KleinFractalModel{
  Fraction special_fract;

	public:
		MobiusT *generators;
		vector<vector<complex<float>>> fixedPoints;
		
	private:
		void compute_fixed_points();
};

#endif
