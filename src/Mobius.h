#ifndef Mobius_h
#define Mobius_h

#include <cmath>
#include <complex>

using namespace std;

class MobiusT{
	complex<float> a;
	complex<float> b;
	complex<float> c;
	complex<float> d;
	public:
		complex<float> apply(complex<float> z);
		MobiusT compose(MobiusT a);
		MobiusT(complex<float> a_n, complex<float> b_n, complex<float> c_n, complex<float> d_n);
};	

#endif
