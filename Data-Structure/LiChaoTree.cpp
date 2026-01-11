namespace lichao {
    struct line {
        long long a = 0, b = inf;
        line() {}
        line(long long a, long long b) : a(a), b(b) {}
        long long operator()(ll x) const { return a * x + b; }
    };
    vector<line> st;
    vl pts;
    void init() { st.clear(); pts.clear(); }
    void addpt(ll x) { pts.push_back(x); }
    void orderpts() {
        sort(ALL(pts));
        pts.erase(unique(ALL(pts)), pts.end());
        st.resize(4LL * (pts.size() + 5));
    }
    int lc(int x) { return 2 * x + 1; }
    int rc(int x) { return 2 * x + 2; }
    void update(int o, int l, int r, line tl, ll a, ll b) {
        if (l > r || pts[r]<a || pts[l]>b) return;
        int mid = (l + r) / 2;
        if (a <= pts[l] && pts[r] <= b) {
            if (st[o].a < tl.a) swap(st[o], tl);
            if (st[o](pts[mid]) < tl(pts[mid])) {
                if (l != r) update(rc(o), mid + 1, r, tl, a, b);
            }
            else {
                swap(st[o], tl);
                if (l != r) update(lc(o), l, mid, tl, a, b);
            }
            return;
        }
        update(lc(o), l, mid, tl, a, b);
        update(rc(o), mid + 1, r, tl, a, b);
    }
    ll query(int o, int l, int r, ll x) {
        if (l > r) return inf;
        if (l == r)return st[o](x);
        int mid = (l + r) / 2;
        if (x <= pts[mid]) return min(st[o](x), query(lc(o), l, mid, x));
        else return min(st[o](x), query(rc(o), mid + 1, r, x));
    }
}