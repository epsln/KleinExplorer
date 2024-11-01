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
	d_n = d * m.b + d * m.d;
	return MobiusT(a_n, b_n, c_n, d_n);
}

void MobiusT::compute_fixed_points(vector<complex<float>>& fp){
	//TODO: Find a cleaner way of doing this (creating and pushing a 1D array into 2D)
	fp.clear();
	if (c == (complex<float>)0 && a !=  d){
		fp.push_back(-b/(a - d));
		return;
	}
	complex<float> z0 = (a - d) + sqrt(pow(a - d, 2) + float(4) * b * c)/(float(2) * c);
	complex<float> z1 = (a - d) - sqrt(pow(a - d, 2) + float(4) * b * c)/(float(2) * c);
	fp.push_back(z0);
	fp.push_back(z1);
	//TODO: Check multiplicity of roots
	return;
}

MobiusT MobiusT::inverse(){
	return MobiusT(d, -b, -c, a);
}

void MobiusT::print(){
	ofLog(OF_LOG_NOTICE, "[%f %f, %f %f,%f %f, %f %f]", real(a), imag(a), real(b), imag(b), real(c), imag(c), real(d), imag(d)); 
}
