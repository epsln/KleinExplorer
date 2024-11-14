#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include "ofMain.h"

#include "accidents.h"
#include "recipes.h"
#include "klein_fractal_model.h"
#include "fraction.h"

using namespace std;

complex<float> tracePoly(Fraction f, complex<float> ta, complex<float> tB, complex<float> taB){
	//Implementation of the trace recursion algo from pp. 286
	if (f.p == 0 && f.q == 1) return ta;
	else if (f.p== 1 && f.q== 0){
		return tB;
	}


	long int p1, p2, p3;
	long int q1, q2, q3;

	complex<float> tr_u, tr_v, tr_uv, temp;

	p1 = 0;
	q1 = 1;

	p2 = 1;
	q2 = 0;

	p3 = 1;
	q3 = 1;

	tr_u  = ta;
	tr_v  = tB;
	tr_uv = taB;

	while(p3 * f.q != f.p * q3){
		if (f.p * q3 < p3 * f.q){
			p2 = p3;
			q2 = q3;
			p3 = (p1 + p3);
			q3 = (q1 + q3);

			temp = tr_uv;

			tr_uv = tr_u * tr_uv - tr_v;
			tr_v = temp;
		}
		else{
			p1 = p3;
			q1 = q3;
			p3 = (p2 + p3);
			q3 = (q2 + q3);

			temp = tr_uv;

			tr_uv = tr_v * tr_uv - tr_u;
			tr_u = temp;
		}
	}
	return tr_uv;
}


void makeFareySeq(int denum, vector<Fraction> &fractionArr){
	//Code for RosettaCode: https://rosettacode.org/wiki/Farey_sequence#C, with minor modifications to put it all in an array
	Fraction f1 = {0, 1};
	Fraction f2 = {1, denum};
	Fraction t;
	int k = 0;
	int i = 1;

	fractionArr.push_back({0, 1});
	fractionArr.push_back({1, denum});
	while (f2.q > 1){
		i++;
		k = (denum + f1.q)/f2.q;
		t = f1;
		f1 = f2;
		f2 = {f2.p * k - t.p, f2.q * k - t.q};
		fractionArr.push_back(f2);
	}
}

Fraction getNextFareyElem(int denum, Fraction f1, Fraction f2){
	Fraction t;
	int k = (denum + f1.q)/f2.q;
	t = f1;
	f1 = f2;
	return (Fraction) {f2.p * k - t.p, f2.q * k - t.q};
}

void makeFiboSeq(int n, vector<Fraction> &fractionArr){
	int fibo[3] = {0, 1, 1}; 
	int buff = 0;
	//Dirty way of doing fibo serie...
	for (int i = 2; i < n; i++){
		buff = fibo[3];
		fibo[3] = fibo[0] + fibo[1]; 
		fibo[0] = fibo[1];
		fibo[1] = buff;
		fractionArr.push_back({fibo[0], fibo[3]});  	
	}
}

void makeContinuedFraction(int lengthArr, float realNum, vector<Fraction> fractionArr){
	//Creates an array filed with the continued fraction approximation of realNum
	float intPart;
	float reciprocal, num, denum, temp;
	int fractTerms[lengthArr + 1];//Array to hold the values of the denominator of the continued fraction
	if (realNum == 1){
		fractionArr.push_back({1, 1});
		return;
	}

	if (realNum >= 1){
		intPart = floor(realNum);
		realNum = realNum - intPart;
	}

	intPart = floor(realNum);
	reciprocal = 1.0/(realNum - intPart);

	fractTerms[0] = floor(reciprocal);
	for (int i = 1; i < lengthArr; i++){
		intPart = floor(reciprocal);
		if (reciprocal - intPart < 0.0001){
			reciprocal = 1.0/(reciprocal - intPart);
			fractTerms[i] = intPart;
			lengthArr = i;
			break;
		}
		reciprocal = 1.0/(reciprocal - intPart);
		fractTerms[i] = intPart;
	}

	if (lengthArr == 1){
		fractionArr[0] = {1, fractTerms[0]};
	}

	for (int i = 0; i < lengthArr; i++){
		Fraction a = {1, fractTerms[i + 1]};	
		Fraction b = {fractTerms[i], 1};	
		Fraction out = a.add(b);
		for (int j = i - 1; j >= 0; j--){
			if (i == 0 || lengthArr == 2) break;
			a = {fractTerms[j], 1};	
			b = {out.q, out.p};	
			out = a.add(b);
		}
		out = {out.q, out.p};
		out.simplify();
		fractionArr.push_back(out);	
	}
}

void getSpecialWordFromFract(vector<int> &specialWord, Fraction fraction){
	int num = 1; 
	int i = 0;
	int idx = 3;
	int numToAdd = fraction.q;
	do{
		if(num + fraction.q > fraction.p + fraction.q){
			numToAdd = -fraction.p;
			idx = 0;
		}	
		if(num - fraction.p < 1){
			numToAdd = fraction.q;
			idx = 3;
		}	
		num += numToAdd;
		specialWord.push_back(idx);
		i++;
	}while(num != 1);

	num = fraction.q + fraction.p - 1;
	reverse(specialWord.begin(), specialWord.end());
}

void getTraceFromFract(complex<float> *pz0, Fraction fraction){
	//Get the trace of a particular fraction following each farey neighbor
	const complex<float> i(0.0, 1.0);
	Fraction f1 = {0, 1};
	Fraction f2 = {1, fraction.q};
	Fraction f2_prev = f2;
	*pz0 = (float)2 * i;
	newtonSolver(pz0, f1);
	while(fraction.p != f2.p || fraction.q != f2.q){
		newtonSolver(pz0, f2);
		f2 = getNextFareyElem(fraction.q, f1, f2);
		f1 = f2_prev;
		f2_prev = f2;
	}
}

complex<float> traceEqn(Fraction fraction, complex<float> mu){
	const complex<float> i(0.0, 1.0);
	return (tracePoly(fraction, -i*mu, 2, -i * mu + (float)2 * i) - (float)2);
}

void newtonSolver(complex<float> *pz0, Fraction fraction){
	const complex<float> i(0.0, 1.0);
	int maxiter = 100000;
	complex<float> z = *pz0;
	float epsilon = 1E-6;
	complex<float> realVal, imagVal, deriv;
	complex<float> traceEqVal;

	//Carefull, without a imaginary part, newton doesnt converge !
	if (imag(*pz0) == 0)
		*pz0 += i;

	if( isinf(imag(traceEqn(fraction, z))) || isnan(imag(traceEqn(fraction, z)))){
		ofLog(OF_LOG_FATAL_ERROR, "Newton method failed! Getting infinity \n");
		exit(-1);
	}
	for (int i = 0; i < maxiter; i++){
		//Compute the complex derivate using a simple finite differences scheme on real and imag axis
		realVal = (traceEqn(fraction, z + epsilon)     - traceEqn(fraction, z - epsilon))/(2*epsilon);
		imagVal = (traceEqn(fraction, z + epsilon * i) - traceEqn(fraction, z - epsilon * i))/(2 * epsilon * i);
		deriv = (realVal + imagVal)/(float)2;
		//Update the guess 	
		traceEqVal = traceEqn(fraction, z);
		z = z - traceEqVal/deriv;
		if (abs(traceEqVal) <= 1E-5 && abs(z - *pz0) <= 1E-4)
			return;
		else
			*pz0 = z;
	}
	ofLog(OF_LOG_FATAL_ERROR, "Newton method failed! Not converging after %d iterations. Last value: %f %f\n", maxiter, real(z), imag(z));
	exit(-1);
}

void getGeneratorsFromFraction(KleinFractalModel &kfm, Fraction f){
	const complex<float> i(0.0, 1.0);
	vector<int> specialWord;
	complex<float> z;
	complex<float> *pz = &z;
	getSpecialWordFromFract(specialWord, f);
	getTraceFromFract(pz, f);
	MobiusT generators[4];
	grandmaRecipe(-i * z, 2, generators);
	KleinFractalModel(generators, f);
}
