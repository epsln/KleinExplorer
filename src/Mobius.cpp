#include <cmath>
#include <complex>

#include "Mobius.h"

using namespace std;

MobiusT::MobiusT(complex<float> a_n, complex<float> b_n, complex<float> c_n, complex<float> d_n){
	a = a_n;
	b = b_n;
	c = c_n;
	d = d_n;
}

complex<float> MobiusT::apply(complex<float> z){
	return (a * z + b)/(c * z + d);
}

MobiusT MobiusT::compose(MobiusT m){
	complex<float> a_n, b_n, c_n, d_n;	
	a_n = a * m.a + b * m.c;
	b_n = a * m.b + b * m.d;
	c_n = c * m.a + d * m.c;
	d_n = d * m.b + d * m.d;
	return MobiusT(a_n, b_n, c_n, d_n);
}
