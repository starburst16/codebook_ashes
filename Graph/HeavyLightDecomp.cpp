const int maxn = 1e5 + 5;
int u[maxn], v[maxn], w[maxn];
int p[maxn], dep[maxn], sz[maxn], to[maxn];
int tp[maxn], dfn[maxn], st[maxn * 4], tk;
vector<int> g[maxn];

void dfs(int u, int fa) {
    dep[u] = ~fa ? dep[fa] + 1 : 0;
    fa[u] = fa;
    sz[u] = 1;
    to[u] = -1;

    for (int i = 0; i < (int)g[u].size(); ++i) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (to[u] == -1 || sz[v] > sz[to[u]]) swap(to[u], v);
    }
}
// dfs(root,-1)
void hld(int u, int f) {
    tp[u] = f; dfn[u] = tk++;
    if (~to[u]) hld(to[u], f);

    for (int i = 0; i < (int)g[u].size(); ++i) {
        int v = g[u][i];
        if (v == fa[u] || v == to[u]) continue;
        hld(v, v);
    }
}
// hld(root,root)
void modify(int l, int r, int ql, int qr, int v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) return st[o] = min(st[o], v), void();
    modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
}

int query(int l, int r, int p, int o = 0) {
    if (r - l == 1) return st[o];
    if (p < (l + r) >> 1) return min(st[o], query(l, (l + r) >> 1, p, o * 2 + 1));
    else return min(st[o], query((l + r) >> 1, r, p, o * 2 + 2));
}

vector<pair<int, int>> get(int x, int y) {
  int fx = tp[x], fy = tp[y];
  vector<pair<int, int>> res;
  while (fx != fy) {
    if (dep[fx] < dep[fy]) {
      swap(fx, fy);
      swap(x, y);
    }
    res.emplace_back(dfn[fx], dfn[x] + 1);
    x = fa[fx];
    fx = tp[x];
  }
  res.emplace_back(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]) + 1);
  int lca = (dep[x] < dep[y] ? x : y);
  return res;
}