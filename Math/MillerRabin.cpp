//Deterministic version
long long quick_pow(long long x, long long p, long long mod) { 
    long long ans = 1;
    while (p) {
        if (p & 1) ans = (__int128)ans * x % mod;
        x = (__int128)x * x % mod;
        p >>= 1;
    }
    return ans;
}
bool check_composite(ll n, ll a, ll d, int s) {
    ll x = quick_pow(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};
bool MillerRabin(ll n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;
    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

