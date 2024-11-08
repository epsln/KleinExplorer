#ifndef accidents_h
#define accidents_h

#include <complex>
#include <cmath>
#include <vector>

#include "fraction.h"

complex<float> tracePoly(Fraction f, complex<float> ta, complex<float> tB, complex<float> taB);
complex<float> traceEqn(Fraction f, complex<float> mu);
void makeFareySeq(int denom, vector<Fraction> &fractionArr);
void makeFiboSeq(int lengthAnim, vector<Fraction> &fractionArr);
int makeContinuedFraction(int lengthAnim, float real, vector<Fraction> &fractionArr);

void getTraceFromFract(complex<float> *pz0, Fraction f);
void getSpecialWordFromFract(vector<int> &specialWord, Fraction f);

void newtonSolver(complex<float> *pZ0, Fraction f);
#endif
