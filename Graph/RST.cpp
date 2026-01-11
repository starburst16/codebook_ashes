const int maxn = 2e5 + 5;

int n, m, q;
int od[maxn], cir[maxn], sz;
namespace RST{
	const int log = 20;
	int dis[maxn], dep[maxn], f[maxn][log];
	vector<pi> adj[maxn];
	inline void add(int a, int b, int c){
		adj[a].emplace_back(b, c);
	}
	void dfs(int u, int fa){
		f[u][0] = fa;
		dep[u] = dep[fa] + 1;
		for (int i = 1; i < log; i++){
			f[u][i] = f[f[u][i-1]][i-1];
		}
		for (auto [v, w] :adj[u]){
			dis[v] = dis[u] + w;
			dfs(v, u);
		}
	}
	int query(int x, int y){
		if (dep[x] < dep[y]) swap(x, y);
		int u = x, v = y;
		int d = dep[u] - dep[v];
		for (int i = 0; i < log; i++){
			if (d >> i & 1){
				u = f[u][i];
			}
		}
		if (u == v) return dis[x] - dis[y];
		for (int i = log-1; i >= 0; i--){
			if (f[u][i] != f[v][i]){
				u = f[u][i];
				v = f[v][i];
			}
		}
		int lca = f[u][0];
		if (lca <= n) return dis[x] + dis[y] - 2 * dis[lca];
		d = abs(od[u] - od[v]);
		return dis[x] - dis[u] + dis[y] - dis[v] + min(d, cir[lca] - d);
	}
}

vector<pi> adj[maxn];
int dfn[maxn], low[maxn], timer;
int be[maxn], stk[maxn], top;
void tarjan(int u, int fa){
	dfn[u] = low[u] = ++timer;
	stk[++top] = u;
	for (auto[v, w]:adj[u]){
		if (v == fa) continue;
		if (!dfn[v]){
			od[v] = od[u] + w;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] == dfn[u]){
				cir[++sz] = be[u];
				RST::add(u, sz, 0);
				for (int t = -1, j = top; t != v; ){
					t = stk[j--];
					cir[sz] += od[t] - od[stk[j]];
				}
				while(true){
					int d = od[stk[top]] - od[u];
					RST::add(sz, stk[top], min(d, cir[sz] - d));
					if (stk[top--] == v) break;
				}
			}else if (low[v] > dfn[u]){
				RST::add(u, v, w);
				top--;
			}
		}else{
			be[v] = w;
			low[u] = min(low[u], dfn[v]);
		}
	}
}