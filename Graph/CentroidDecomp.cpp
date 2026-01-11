const int maxn = 2e5 + 5;
vector<int> adj[maxn], cand;
int sz[maxn], mx[maxn], vis[maxn], cnt[maxn];
int max_dep;

int n, k;
ll ans = 0;

void get_size(int u, int fa) {
  cand.push_back(u);
  sz[u] = 1, mx[u] = 0;
  for (int v:adj[u]){
    if (vis[v] || v == fa) continue;
    get_size(v, u);
    mx[u] = max(mx[u], sz[v]);
    sz[u] += sz[v];
  }
}
void get_dis(int u, int fa, bool add, int dep) {
  if (dep > k) return;
  max_dep = max(max_dep, dep);
  if (add) ans += cnt[k - dep];
  else cnt[dep]++;
  for (int v:adj[u]) if (!vis[v] && v != fa) {
    get_dis(v, u, add, dep+1);
  }
}
void dfs(int u) {
  get_size(u, u);
  int c = -1, all = cand.size();
  for (int v:cand){
    if (max(mx[v], all - sz[v]) <= all / 2) c = v;
  }
  cand.clear();
  vis[c] = true;

  max_dep = 0;
  cnt[0] = 1;
  for (int v:adj[c]){
    if (!vis[v]){
      get_dis(v, c, true, 1);
      get_dis(v, c, false, 1);
    }
  }
  fill(cnt + 1, cnt + max_dep + 1, 0);
  for (int v:adj[c]){
    if (!vis[v]){
        dfs(v);
    }
  }
}