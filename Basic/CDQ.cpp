struct node{
    int a, b, c;
    int id;
};

bool cmpA(node x, node y) {
  if (x.a != y.a) return x.a < y.a;
  if (x.b != y.b) return x.b < y.b;
  return x.c < y.c;
}

bool cmpB(node x, node y) {
  if (x.b != y.b) return x.b < y.b;
  return x.c < y.c;
}

// res[i] = #(j, a[j] < a[i], b[j] < b[i], c[j] < c[i])
// bit.query(i) = pref(0~i-1)
void solve(){
    vector<node> A(n+1);
    for (int i = 0; i <= n; i++){
        A[i].a = a[i];
        A[i].b = b[i];
        A[i].c = c[i];
        A[i].id = i;
    }
    sort(ALL(A), cmpA);

    fenwick bit(n+1);
    vector<int> res(n+1);

    function<void(int, int)> CDQ = [&](int l, int r){
        if (l == r || A[l].a == A[r].a) return;

        int mid = (l + r) >> 1;
        int target = 0;
        for (int i = l; i < r; i++){
            if (A[i].a != A[i+1].a){
                if (abs(i - mid) < abs(target - mid)){
                    target = i;
                }
            }
        }

        mid = target;
        CDQ(l, mid); CDQ(mid+1, r);

        sort(A.begin()+l, A.begin()+mid+1, cmpB);
        sort(A.begin()+mid+1, A.begin()+r+1, cmpB);

        for (int i = l, j = mid+1; j <= r; j++){
            while (i <= mid && A[i].b < A[j].b){
                bit.add(A[i].c, 1);
                i++;
            }
            res[A[j].id] = max(res[A[j].id], bit.sum(A[j].c));
        }

        for (int i = l; i <= mid; i++){
            bit.add(A[i].c, -1);
        }

    };

}
