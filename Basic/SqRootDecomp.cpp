
const int N = 2e5+5e4;
const int S = 1e6+5;
int k;

struct query{
	int l, r, t, id;
	bool operator < (query b){
		return (l/k==b.l/k  ? (r/k == b.r/k ? t < b.t : r/k < b.r/k) : l/k < b.l/k);
	}
} Q[N];


struct upd{
	int pos,x;
} M[N];	

int arr[N], cnt[S], ans[N], tmp;

void add(int val){
	if(!cnt[val]) tmp++;
	cnt[val]++;
}

void sub(int val){
	cnt[val]--;
	if(!cnt[val]) tmp--;
}

void modify(query x, upd &y){
	if(x.l <= y.pos && y.pos <= x.r){
		sub(arr[y.pos]);
		add(y.x);
	}
	swap(arr[y.pos],y.x);
}

signed main(){
	fastio
	int n, m;
	cin >> n >> m;
	k = pow(n,(double)2/(double)3);
	for(int i = 1;i <= n;i++) cin >> arr[i];
	int tid = 0, qid = 0;
	for(int i = 0;i < m;i++){
		char q;
		cin >> q;
		if(q=='Q'){
			int l, r;
			cin >> l >> r;
			Q[qid] = {l,r,tid,qid};
			qid++;
		}else{
			int x, val;
			cin >> x >> val;
			++tid;
			M[tid] = {x,val};
		}
	}
	sort(Q,Q+qid);
	int l = 1, r = 0, t = 0;
	for(int i = 0;i < qid;i++){
		auto q = Q[i];
		while(l < q.l) sub(arr[l++]);
		while(l > q.l) add(arr[--l]);
		while(r < q.r) add(arr[++r]);
		while(r > q.r) sub(arr[r--]);
		while(t < q.t) modify(Q[i],M[++t]);
		while(t > q.t) modify(Q[i],M[t--]);
		ans[q.id] = tmp;
	}
	for(int i = 0;i < qid;i++) cout << ans[i] << "\n";
}