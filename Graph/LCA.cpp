const int mxN = 1e5+5, LOG = 18;
vector<int> adj[mxN];
int dep[mxN], up[mxN][LOG];
void dfs(int u, int p){
  for (int v:adj[u]){
    if (v == p)
      continue;
    dep[v] = dep[u] + 1;
    up[v][0] = u;
    for (int j = 1; j < LOG; j++){
      up[v][j] = up[up[v][j - 1]][j - 1];
    }
    dfs(v, u);
  }
}
int lca(int u, int v){
	if(dep[u] < dep[v])
		swap(u, v);
	int k = dep[u] - dep[v];
	for(int j = LOG - 1; j >= 0; j--) {
		if(k & (1 << j)) {
			u = up[u][j]; 
		}
	}
	if(u == v) {
		return u;
	}
	for(int j = LOG - 1; j >= 0; j--) {
		if(up[u][j] != up[v][j]) {
			u = up[u][j];
			v = up[v][j];
		}
	}
	return up[u][0];
}
