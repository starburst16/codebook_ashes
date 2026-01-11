vector<int> pr, lf;
void comp(int n) {
	for (int i = 0; i < n; i++) {
		lf.push_back(0);
	}
	lf[0] = 1; lf[1] = 1;
	for (int i = 2; i < n; i++) {
		if (lf[i] == 0) {
			pr.push_back(i);
			lf[i] = i;
		}
		for (int p:pr){
			if (i * p >= n || p > lf[i]) break;
			lf[i * p] = p;
		}
	}
}