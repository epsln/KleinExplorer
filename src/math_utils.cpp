#include <vector>
#include "math_utils.h"

using namespace std;

int mod(int a, int b){
	//Special mod that also works for negative inputs
	int r = a % b;
	if (r < 0)
		return r + b;
	else
		return r;
}

void cyclic_permutation(vector<int>& word, vector<int>& cyclic_perm, int shift){
	//Compute a cyclic permutation for the input word
	cyclic_perm.clear();
	for (int i = 0; i < word.size(); i++){
		cyclic_perm.push_back(word[mod((i + shift) , word.size())]);
	}
}

int gcd(int a, int b){
	int temp;
	while (b != 0){
		temp = a % b;

		a = b;
		b = temp;
	}
	return a;
}
