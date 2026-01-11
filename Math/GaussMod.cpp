const int mod = 998244353;

int modpow(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = (ll)res * x % mod;
    x = (ll)x * x % mod;
    y >>= 1;
  }
  return res;
}

// {rank, one of the solution, basis}
tuple<int, vector<int>, vector<vector<int>>> gauss(vector<vector<int>> &a) { 
	int n = a.size(), m = a[0].size()-1;
    int k = 0, R = m;
	vector<int> fix(m, -1);
	for (int i = 0; i < m; i++) {
		int j = k;
		while (j < n && a[j][i] == 0) j++;
		// for (int j = k; j < n; j++) if (a[j][i]) break;
		if (j == n) continue;
		fix[i] = k; --R;
		swap(a[k],a[j]);
		int *u = a[k].data();
		int x = modpow(u[i], mod - 2);
		for (int j = i; j <= m; j++) u[j] = (ll)u[j] * x % mod;
		for (auto &v:a) if (v.data() != a[k].data())
		{
			x = mod - v[i];
			for (int j = i; j <= m; j++) v[j] = (v[j] + (ll) x * u[j]) % mod;
		}
		++k;
	}
	for (int i = k; i < n; i++) if (a[i][m]) return {-1, {}, {}};
	vector<int> r(m);
	vector<vector<int>> c;
	for (int i = 0; i < m; i++) if (fix[i] != -1) r[i]=a[fix[i]][m];
	for (int i = 0; i < m; i++) if (fix[i] == -1)
	{
		vector<int> r(m);
		r[i] = 1;
		for (int j = 0; j < m; j++) if (fix[j] != -1) r[j] = (mod - a[fix[j]][i]) % mod;
		c.push_back(r);
	}
	return {R, r, c};
}