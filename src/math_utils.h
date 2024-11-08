#ifndef math_utils_h
#define math_utils_h

#include <vector>

using namespace std;

int mod(int a, int b);
int gcd(int a, int b);
void cyclic_permutation(vector<int>& word, vector<int>& cyclic_perm, int shift);

#endif
