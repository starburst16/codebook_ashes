using LLL = __int128;
ll modpow(ll e, ll p, ll m) {
	ll r = 1;
	while (p) {
		if (p & 1) r = (LLL)r * e % m;
		e = (LLL)e * e % m;
		p >>= 1;
	}
	return r;
}
ll modmul(ll a, ll b, ll m) {
	return (LLL)a * b % m;
}
map<long long, int> cnt;
void PollardRho(long long n) {
	if (n == 1) return;
	if (MillerRabin(n)) return ++cnt[n], void();
	if (n % 2 == 0) return PollardRho(n / 2), ++cnt[2], void();
	long long x = 2, y = 2, d = 1, p = 1;
	auto f = [&](auto x, auto n, int p) { return (modmul(x, x, n) + p) % n; };
	while (true) {
		if (d != n && d != 1) {
			PollardRho(n / d);
			PollardRho(d);
			return;
		}
		if (d == n) ++p;
		x = f(x, n, p); y = f(f(y, n, p), n, p);
		d = gcd(abs(x - y), n);
	}
}
