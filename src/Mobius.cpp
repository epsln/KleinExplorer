#include <cmath>
#include <complex>
#include <vector>

#include "ofMain.h"
#include "Mobius.h"

using namespace std;

MobiusT::MobiusT(complex<float> a_n, complex<float> b_n, complex<float> c_n, complex<float> d_n){
	a = a_n;
	b = b_n;
	c = c_n;
	d = d_n;
}

MobiusT::MobiusT(){
	a = 0;
	b = 0;
	c = 0;
	d = 0;
}

complex<float> MobiusT::apply(complex<float> z){
	return (a * z + b)/(c * z + d);
}

MobiusT MobiusT::compose(MobiusT m){
	complex<float> a_n, b_n, c_n, d_n;	
	a_n = a * m.a + b * m.c;
	b_n = a * m.b + b * m.d;
	c_n = c * m.a + d * m.c;
	d_n = c * m.b + d * m.d;
	return MobiusT(a_n, b_n, c_n, d_n);
}

complex<float> MobiusT::compute_fixed_points(){
	if (c == (complex<float>)0 && a !=  d){
		return -b/(a - d);
	}
	complex<float> k = pow(((a + d) + sqrt(pow((a + d), 2) - (float)4))/(float)2, 2);
	if (abs(k) > 1)
		return (a - d + sqrt(pow(d - a, 2) + float(4) * b * c))/(float(2) * c); 
	else
		return (a - d - sqrt(pow(d - a, 2) + float(4) * b * c))/(float(2) * c); 
}

MobiusT MobiusT::inverse(){
	return MobiusT(d, -b, -c, a);
}

void MobiusT::print(){
	ofLog(OF_LOG_VERBOSE, "[%f %f, %f %f,%f %f, %f %f]", real(a), imag(a), real(b), imag(b), real(c), imag(c), real(d), imag(d)); 
}
