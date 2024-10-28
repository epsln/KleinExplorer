#ifndef Fraction_h
#define Fraction_h

class Fraction {
	int p, q;
	public:
		Fraction(int p_, int q_);
		Fraction add(Fraction f);
		Fraction sub(Fraction f);
		Fraction mul(Fraction f);
		Fraction div(Fraction f);
		Fraction cailey_add(Fraction f);
};

#endif
