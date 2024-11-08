#ifndef accidents_h
#define accidents_h

#include "fraction.h"

complex<float> tracePoly(Fraction q, complex ta, complex<float> tB, complex<float> taB);
complex<float> traceEqn(Fraction q, complex<float> mu);
void makeFareySeq(int denom, vector<Fraction> &fractionArr);
void makeFiboSeq(int lengthAnim, vector<Fraction> &fractionArr);
int makeContinuedFraction(int lengthAnim, double real, vector<Fraction> &fractionArr)

void getTraceFromFract(complex<float> *pz0, Fraction q);
void getSpecialWordFromFract(vector<int> &specialWord, Fraction q);

void newtonSolver(complex<float> *pZ0, Fraction q);
#endif
