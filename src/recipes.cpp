#include <complex>
#include <cmath>

#include "recipes.h"
#include "Mobius.h"

using namespace std;

void maskitRecipe(complex<float> ta, MobiusT gens[4]){
	//See pp. 259
	//
	const complex<float> i(0.0, 1.0);

	MobiusT a = MobiusT(ta, -i, -i, 0);
	MobiusT b = MobiusT(1, 2, 0, 1);
	MobiusT A = a.inverse();
	MobiusT B = b.inverse();

	gens[0] = a;
	gens[1] = b;
	gens[2] = A;
	gens[3] = B;
}

void grandmaRecipe(complex<float> ta, complex<float> tb, MobiusT* gens){
	if (ta == (float)0 && tb == (float)0){
		printf("Error ! ta and tb cannot be both == 0 !\n Exiting...\n");
		exit(-3);
	}
	const complex<float> i(0.0, 1.0);
	//Couldnt figure out a better way to multiply complex floats with anything
	//WTF C++ ???
	const float two = (float) 2;
	const float four = (float) 4;

	complex<float> a = 1;
	complex<float> b = (-ta * tb);
	complex<float> c = ta * ta + tb * tb;
	complex<float> delta = b*b - four * a * c; 
	complex<float> tab = (- b - sqrt(delta))/(two * a); 
	complex<float> z0 = ((tab - two) * tb)/(tb * tab - two * ta + two * i * tab);

	MobiusT ma = MobiusT(ta/two, (ta*tab - two * tb + four * i)/(z0*(two * tab + four)),
										  ((ta * tab - two * tb - four * i)*z0)/(two * tab - four), ta/two);

	MobiusT mb = MobiusT((tb - two * i)/two, tb/two, tb/two, (tb + two * i)/two);
	MobiusT mA = ma.inverse();
	MobiusT mB = mb.inverse();

	gens[0] = ma;
	gens[1] = mb;
	gens[2] = mA;
	gens[3] = mB;
}

void grandmaSpecialRecipe(complex<float> ta, complex<float> tb, complex<float> tab, MobiusT* gens){
	//Grandma's Special four-alarm two generator group recipe 
	//See pp. 261
	//	printf("ta:  %lf + %lf\n", creal(ta), cimag(ta));
	//	printf("tb:  %lf + %lf\n", creal(tb), cimag(tb));
	//	printf("tab: %lf + %lf\n", creal(tab), cimag(tab));
	const complex<float> i(0.0, 1.0);
	const float two = (float) 2;
	const float four = (float) 4;

	complex<float> tc = ta * ta + tb * tb + tab * tab - ta * tb * tab - two;
	complex<float> Q  = sqrt(two - tc);	
	complex<float> R = 0;

	if (abs(tab) == two){ 
		printf("Error ! taB cannot be == +/- 2 !\n Exiting...\n");
		exit(-3);
	}
	if (abs(tc + i * Q * sqrt(tc + two)) >= two)
		R = sqrt(tc + two);
	else
		R = -sqrt(tc + two);

	complex<float> z0 = ((tab - two) * (tb + R))/(tb * tab - two * ta + i * Q * tab);

	MobiusT a = MobiusT(ta/two,  (ta * tab - two * tb + two * i * Q)/(z0 * (two * tab + four)), 
											((ta * tab - two * tb - two * i * Q) * z0)/(two * tab - four), ta/two);

	MobiusT b = MobiusT((tb - i * Q)/two, (tb * tab - two * ta - i * Q * tab)/(z0 * (two * tab + four)), 
											((tb * tab - two * ta + i * Q * tab) * z0)/(two * tab - four), (tb + i * Q)/two);  

	MobiusT A = a.inverse();
	MobiusT B = b.inverse();

	gens[0] = a;
	gens[1] = b;
	gens[2] = A;
	gens[3] = B;
}

void jorgensen(complex<float> ta, complex<float> tb, MobiusT* gens){
	const complex<float> i(0.0, 1.0);
	const float two = (float) 2;
	const float four = (float) 4;

	complex<float> z   = 1/two * sqrt(ta * ta * tb * tb - four * ta * ta - four * tb * tb);
	complex<float> tab = 1/two * (ta * tb) - z;

	MobiusT a = MobiusT(ta - tb / tab, ta / (tab * tab), ta, tb/tab);
	MobiusT b = MobiusT(tb - ta / tab, -tb, -tb, ta / tab);

	MobiusT A = a.inverse();
	MobiusT B = a.inverse();

	gens[0] = a;
	gens[1] = b;
	gens[2] = A;
	gens[3] = B;
}
