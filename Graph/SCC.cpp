const int maxn = 1e5 + 10;
vi G[maxn];
vi rG[maxn];
bool vst[maxn];
vi vs;
int id[maxn];
void add_edge(int u, int v) {
	G[u].push_back(v);
	rG[v].push_back(u);
}
void dfs(int u) {
	if (vst[u]) return;
	vst[u] = true;
	for (int v:G[u]) dfs(v);
	vs.push_back(u);
}
void rdfs(int u, int k) {
	if (vst[u]) return;
	vst[u] = true; id[u] = k;
	for (int v : rG[u] ) rdfs(v, k);
}
int scc(int n) {
	fill(vst,vst+n+1,false);vs.clear();
	for (int i = 1; i <= n; i++) if(!vst[i]) dfs(i);
	for (int i = 1; i <= n; i++) vst[i] = false;
	int k = 0;
	for (int i = vs.size() - 1; i >= 0; i--) {
		if (!vst[vs[i]]) {
			rdfs(vs[i], k); k++;
		}
	}
	return k;
}
