double* initDoubleMass(int c, const double d[]) {
	double* tmp = new double[c];
	for (int i = 0; i < c; i++) {
		tmp[i] = d[i];
	}
	return tmp;
}