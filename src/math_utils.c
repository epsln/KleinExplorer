int mod(int a, int b){
	int r = a % b;
	if (r < 0)
		return r + b;
	else
		return r;
}
