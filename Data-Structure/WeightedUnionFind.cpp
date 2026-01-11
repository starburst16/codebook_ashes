struct WDSU {
    vl ws;
    vi par, rnk;
    vector<vl> his;
    void init(int n) {
        ws.resize(n + 5); par.resize(n + 5); rnk.resize(n + 5);
        for (int i = 0; i < n + 5; i++) ws[i] = 0, par[i] = i, rnk[i] = 0;
        his.clear();
    }
    pair<int, ll> find(int x) {
        if (x == par[x]) return make_pair(x, 0LL);
        ll allw = 0;
        int p = x;
        while (p != par[p]) allw += ws[p], p = par[p];
        return make_pair(p, allw);
    }
    bool unite(int a, int b, ll w) {
        // b -> a with w
        auto infoa = find(a);
        auto infob = find(b);
        int ra = infoa.first, rb = infob.first;
        ll wa = infoa.second, wb = infob.second;
        if (ra == rb) return false;
        if (rnk[ra] < rnk[rb]) {
            // ra -> rb
            his.push_back({ ra, par[ra], ws[ra], rnk[ra] == rnk[rb],rb });
            par[ra] = rb; ws[ra] = wb - w - wa;
        }
        else {
            // rb -> ra
            his.push_back({ rb, par[rb], ws[rb], rnk[ra] == rnk[rb],ra });
            if (rnk[ra] == rnk[rb]) rnk[ra]++;
            par[rb] = ra; ws[rb] = w + wa - wb;
        }
        return true;
    }
    void undo(int cnt) {
        assert(his.size() >= cnt);
        for (int _ = 0; _ < cnt; _++) {
            auto op = his.back(); his.pop_back();
            ll who = op[0], p = op[1], w = op[2], rk = op[3], other = op[4];
            if (rk) rnk[other]--;
            par[who] = p; ws[who] = w;
        }
    }
    ll diff(int a, int b) {
        auto infoa = find(a), infob = find(b);
        if (infoa.first != infob.first) return inf;
        return infob.second - infoa.second;
    }
    bool same(int a, int b) { return find(a).first == find(b).first; }
};
// usage:
// connect: if (!wdsu.same(a, b)) cnt += wdsu.unite(a, b, x);
// contradiction: if (w != wdsu.diff(a,b)) {...} 