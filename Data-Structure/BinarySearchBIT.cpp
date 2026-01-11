int kth(int k){
    int pos = 0;
    int n = maxn-1;
    for (int i = 1 << __lg(n); i; i>>=1){
        if (pos + i <= n && bit[pos + i] < k){
            pos += i;
            k -= bit[pos];
        }
    }
    if (pos == n) return -1;
    return pos+1;
}