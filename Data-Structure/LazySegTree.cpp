struct node{
	ll sum1;
    ll sum2;
    bool lz;
	ll lzAdd;
	ll lzSet;
	node(){};
}seg[maxN*4+5];

#define lc v<<1
#define rc (v<<1)+1

inline void pull(int v){
	seg[v].sum1 = seg[lc].sum1 + seg[rc].sum1;
    seg[v].sum2 = seg[lc].sum2 + seg[rc].sum2;
}

inline ll sum1(int l, int r){
    return r-l+1;
}

inline ll sum2(int l, int r){
    return 1LL * (r-l+1) * (l+r) / 2;
}

void st(int v, int l, int r, ll val){
    seg[v].lz = true;
    seg[v].lzSet = val;
    seg[v].lzAdd = 0;
    seg[v].sum1 = val * sum1(l, r);
    seg[v].sum2 = val * sum2(l, r);
}

void add(int v, int l, int r, ll val){
    seg[v].lzAdd += val;
    seg[v].sum1 += val * sum1(l, r);
    seg[v].sum2 += val * sum2(l, r);
}

void pushdown(int v, int l, int r){
    int m = (l + r) >> 1;
	//lazy: range set
	if(seg[v].lz){
        st(lc, l, m, seg[v].lzSet);
        st(rc, m+1, r, seg[v].lzSet);
		seg[v].lzSet = 0;
        seg[v].lz = false;
	}
    //lazy: range add
    if(seg[v].lzAdd != 0){ 
        add(lc, l, m, seg[v].lzAdd);
        add(rc, m+1, r, seg[v].lzAdd);
        seg[v].lzAdd = 0;
	}
}

void build(int v, int l, int r){
	seg[v].lzAdd = seg[v].lzSet = 0;
    seg[v].lz = false;
	if(l == r){
		seg[v].sum1 = a[l];
        seg[v].sum2 = a[l] * l;
		return;
	}
	int m = (l+r)>>1;
	build(lc, l, m);
	build(rc, m+1, r);
	pull(v);
}

void add(int v, int l, int r, int a, int b, ll val){
	if(a > r || b < l) return;
	if(a <= l && r <= b){
        add(v, l, r, val);
		return;
	}
    pushdown(v, l, r);
	int m = (l+r)>>1;
	add(lc, l, m,a ,b , val);
	add(rc, m+1, r, a, b, val);
	pull(v);
	return;
}

void st(int v, int l, int r, int a, int b, ll val){
	if(a > r || b < l)return;
	if(a <= l && r <= b){
		st(v, l, r, val);
		return;
	}
    pushdown(v, l, r);
	int m = (l+r)>>1;
    st(lc, l, m, a, b, val);
    st(rc, m+1, r, a, b, val);
    pull(v);
	return;
}

ll query1(int v, int l, int r, int a, int b){
	if(a > r || b < l)return 0;
	if(a <= l && r <= b) return seg[v].sum1;
    pushdown(v, l, r);
    int m = (l+r) >> 1;
    ll lres = query1(lc, l, m, a, b);
    ll rres = query1(rc, m+1, r, a, b);
    // pull(v);
    return lres + rres;
}

