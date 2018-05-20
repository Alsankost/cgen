int* initIntMass(int c, const int d[]) {
	int* tmp = new int[c];
	for (int i = 0; i < c; i++) {
		tmp[i] = d[i];
	}
	return tmp;
}