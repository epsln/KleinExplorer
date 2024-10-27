#ifndef Mobius 
#define Mobius 

#include <cmath>
#include <complex>
using namespace std;

class MobiusT{
	complex<float> a;
	complex<float> b;
	complex<float> c;
	complex<float> d;
	public:
		complex<float> fixedPoints[2];

		void computeFixedPoints();
		complex<float> apply(complex<float> z);
		MobiusT compose(MobiusT a);
};	

#endif
