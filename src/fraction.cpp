#include "fraction.h"

Fraction::Fraction(){}

Fraction::Fraction(int p_, int q_){
	p = p_;
	q = q_;
}

Fraction Fraction::add(Fraction f){
	return Fraction(p * f.q + q * f.p, q * f.q);
}

Fraction Fraction::sub(Fraction f){
	return Fraction(p * f.q - q * f.p, q * f.q);
}

Fraction Fraction::mul(Fraction f){
	return Fraction(p * f.p, q * f.q);
}

Fraction Fraction::div(Fraction f){
	return Fraction(p * f.q, q * f.p);
}

Fraction Fraction::cailey_add(Fraction f){
	return Fraction(p + f.p, q + f.q);
}
