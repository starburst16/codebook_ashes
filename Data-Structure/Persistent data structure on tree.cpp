int ls[mxN * LOG], rs[mxN * LOG], val[mxN * LOG];
int rt[mxN];
vector<pi> G[mxN];
int tot;
int insert(int x, int a, int b, int w) {
	int res = ++tot;
	ls[res] = ls[x], rs[res] = rs[x], val[res] = val[x] + 1;
	if (a == b) {
		return res;
	}
	int mid = (a + b) / 2;
	if (w <= mid) {
		ls[res] = insert(ls[res], a, mid, w);
	}
	else {
		rs[res] = insert(rs[res], mid + 1, b, w);
	}
	return res;
}
void dfs(int u, int p) {
 
	for (pi pp : G[u]) {
		int v = pp.first, w = pp.second;
		if (v == p) {
			continue;
		}
		rt[v] = insert(rt[u], 1, 100000, w);
		dfs(v, u);
	}
}
int query(int x, int y, int z, int a, int b, int k) {
	
	if (a == b) {
		return a;
	}
	int mid = (a + b) / 2;
	int num = val[ls[x]] + val[ls[y]] - val[ls[z]] * 2;
	if (k <= num) {
		return query(ls[x], ls[y], ls[z], a, mid, k);
	}
	else {
		return query(rs[x], rs[y], rs[z], mid + 1, b, k - num);
	}
}
int solve(){
	while (q--) {
		int a, b; cin >> a >> b;
		a--; b--;
		int p = lca(a, b);
		int num = dep[a] + dep[b] - dep[p] * 2;
		if (num % 2) {
			int res = query(rt[a], rt[b], rt[p], 1, 100000, num / 2 + 1);
			cout << res << ".0" << "\n";
		}
		else {
			int res1 = query(rt[a], rt[b], rt[p], 1, 100000, num / 2);
			int res2 = query(rt[a], rt[b], rt[p], 1, 100000, num / 2 + 1);
			int res = res1 + res2;
			if (res % 2) cout << res / 2 << ".5" << "\n";
			else cout << res / 2 << ".0" << "\n";
		}
	}
}


