vector<P> convex_hull(vector<P>& ps, int n) {
	auto cmp_x = [&](P& p, P& q) {
		if (p.x != q.x) return p.x < q.x;
		return p.y < q.y;
	};
	sort(ps.begin(), ps.begin() + n, cmp_x);
	int k = 0;
	vector<P> qs(n * 2);
	for (int i = 0; i < n; i++) {
		while (k > 1 && (((qs[k - 1] - qs[k - 2]) ^ (ps[i] - qs[k - 1])) <= 0)) k--;
		qs[k++] = ps[i];
	}
	for (int i = n - 2, t = k; i >= 0; i--) {
		while (k > t && (((qs[k - 1] - qs[k - 2]) ^ (ps[i] - qs[k - 1])) <= 0)) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k - 1);
	return qs;
}
