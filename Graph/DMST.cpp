
struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};
const int inf = 1e9;
pair<int, vector<int>> DMST(int n, int r, vector<Edge> e) {
    // e is REVERSE graph
    int ans = 0;
    vector<int> mn(n, inf), out(n, -1), id(n, -1), vis(n, -1);
    for (int i = 0; i < int(e.size()); i++) {
        if (e[i].u != e[i].v && e[i].w < mn[e[i].u]) {
            mn[e[i].u] = e[i].w;
            out[e[i].u] = i;
        }
    }
    for (int i = 0; i < n; i++){
        if (i != r && out[i] == -1){
            return {-1, {}};
        }
    }
    int cnt = 0;
    auto newe(e);
    for (int u = 0; u < n; u++) {
        if (u == r) {
            continue;
        }
        ans += mn[u];
        int x = u;
        while (vis[x] != u && x != r) {
            vis[x] = u;
            x = e[out[x]].v;
        }
        if (x != r && id[x] == -1) {
            id[x] = cnt;
            for (int i = e[out[x]].v; i != x; i = e[out[i]].v) {
                id[i] = cnt;
            }
            cnt++;
        }
    }
    int circ = cnt;
    if (cnt == 0) {
        out.erase(out.begin() + r);
        return {ans, out};
    }
    for (int i = 0; i < n; i++) {
        if (id[i] == -1) {
            id[i] = cnt++;
        }
    }
    for (auto &[u, v, w] : newe) {
        w -= mn[u];
        u = id[u];
        v = id[v];
    }
    auto [newans, edges] = DMST(cnt, id[r], newe);
    if (newans == -1) return {-1, {}};
    ans += newans;
    for (int i = 0; i < cnt - 1; i++) {
        int u = e[edges[i]].u;
        if (id[u] < circ) {
            for (int i = e[out[u]].v; i != u; i = e[out[i]].v) {
                edges.push_back(out[i]);
            }
        }
    }
    return {ans, edges};
}

