#ifndef KleinFractalModel_h
#define KleinFractalModel_h
#include <vector>

#include "fraction.h"
#include "Mobius.h"

using namespace std;

class KleinFractalModel{
  Fraction special_fract;

	public:
		MobiusT generators[4];
		vector<vector<complex<float>>> fixedPoints;
		
	private:
		void compute_fixed_points();
		KleinFractalModel(MobiusT gen[4], Fraction spe_fract);	
};

#endif
