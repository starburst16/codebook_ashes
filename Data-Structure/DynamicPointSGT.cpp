const int maxn = 2e5 + 5;//query
const int maxsz = 45;//log2(1e9)*const
const int lb = 1,ub = 1000000000;//1e9
typedef struct node {
	ll sum;
	ll lazy;
	int l;
	int r;
}node;
node sgt[maxn * maxsz];
int tot = 1;
void initnode(int x) {
	sgt[x].sum = 0;
	sgt[x].lazy = 0;
	sgt[x].l = sgt[x].r = 0;
}
inline int ls(int x) {return sgt[x].l;}
inline int rs(int x) {return sgt[x].r;}
inline void pull(int x, int l, int r) {
	if (r - l + 1 <= 1) return;
	sgt[x].sum = sgt[ls(x)].sum + sgt[rs(x)].sum;
}

inline void push(int x, int l, int r) {
	if (l > r)  return;
	ll lazy = sgt[x].lazy;
	sgt[x].lazy = 0;
	if (l == r) return;
	if (ls(x) == 0) sgt[x].l = ++tot;
	if (rs(x) == 0) sgt[x].r = ++tot;
	if (lazy == 0) return;
	int mid = (l + r - 1) / 2;
	sgt[ls(x)].lazy += lazy;
	sgt[ls(x)].sum += lazy * (mid - l + 1);
	sgt[rs(x)].lazy += lazy;
	sgt[rs(x)].sum += lazy * (r - mid);
	
}
inline ll query(int x, int l, int r, int a, int b) {
	if (l > r || r<a || l>b) return 0;
	if (a <= l && r <= b) return sgt[x].sum;
	push(x, l, r);
	int mid = (l + r - 1) / 2;
	ll lres = 0, rres = 0;
	if (a <= mid) lres = query(ls(x), l, mid, a, b);
	if (mid < b)  rres = query(rs(x), mid + 1, r, a, b);
	pull(x, l, r);
	return lres + rres;
}
inline void update(int x, int l, int r, int a, int b, ll val) {
	if (l > r || r<a || l>b) return;
	if (a <= l && r <= b) {
		sgt[x].sum += val * (r - l + 1);
		sgt[x].lazy += val;
		return;
	}
	push(x, l, r);
	int mid = (l + r - 1) / 2;
	if (a <= mid) update(ls(x), l, mid, a, b, val);
	if (mid < b) update(rs(x), mid + 1, r, a, b, val);
	pull(x, l, r);
	return;
}
