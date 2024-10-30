#ifndef Recipes_h
#define Recipes_h
#include <complex>
#include "Mobius.h"


//TODO: Couple this with FractalModelFactory with a Recipe as it is more logical
void maskitRecipe(complex<float> ta, MobiusT* gens);

void grandmaRecipe(complex<float> ta, complex<float> tb, MobiusT* gens);

void grandmaSpecialRecipe(complex<float> ta, complex<float> tb, complex<float> tab, MobiusT* gens);

void jorgensen(complex<float> ta, complex<float> tb, MobiusT* gens);

#endif
