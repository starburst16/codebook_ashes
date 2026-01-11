template<typename T>
struct segtree {
	int n;
	vector<T> seg;
    const T ID;

    T comb(T a, T b) {
        assert(a.size() == b.size());
        T c;
        for (int i = 0; i < a.size(); i++){
            c.push_back(b[a[i]]);
        }
        return c;
    }
	// 0-based
	segtree(vector<T> leaves): n(leaves.size()), seg(2*leaves.size()), ID(leaves[0]) {
		copy(begin(leaves), end(leaves), begin(seg)+n);
		for (int i = n-1; i >= 1; i--) {
			seg[i] = comb(seg[2*i], seg[2*i+1]);
		}
	}
	
	void modify(int i, T v) {
		i += n;
		seg[i] = v;
		for (i /= 2; i; i /= 2) {
			seg[i] = comb(seg[2*i], seg[2*i+1]);
		}
	}
	// [l, r)
	T query(int i, int j) {
		i += n, j += n;
		T resl = ID, resr = ID;
		for (; i < j; i /= 2, j /= 2) {
			if (i & 1) resl = comb(resl, seg[i++]);
			if (j & 1) resr = comb(seg[--j], resr);
		}
		return comb(resl, resr);
	}
};


struct node {
    node *l, *r;
    data d;
    node() : l(0), r(0), d() {}
} *root;


#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) return;
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
}

void modify(node *now, int l, int r, int x, int v) {
    if (l == r) {
        now->d.modify(v);
        return;
    }
    if (x <= mid) modify(now->l, l, mid, x, v);
    else modify(now->r, mid + 1, r, x, v);
    now->d = now->l->d + now->r->d;
}

data query(node *now, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return now->d;
    if (qr <= mid) return query(now->l, l, mid, ql, qr);
    if (mid < ql) return query(now->r, mid + 1, r, ql, qr);
    return query(now->l, l, mid, ql, qr) + query(now->r, mid + 1, r, ql, qr);
}