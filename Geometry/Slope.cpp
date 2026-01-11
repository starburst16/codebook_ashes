struct P {
	int x, y, i;
	P() : x(0), y(0), i(-1) {}
};
struct Frac {
	int u, d;
	void norm() {
		if (d == 0) {
			u = u > 0 ? 1 : u < 0 ? -1 : 0;
			return;
		}
		int g = __gcd(u, d);
		u /= g;
		d /= g;
		if (d < 0) {
			d *= -1;
			u *= -1;
		}
	}
};
bool operator > (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d > 1ll * b.u * a.d;
}
bool operator >= (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d >= 1ll * b.u * a.d;
}
bool operator < (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d < 1ll * b.u * a.d;
}
bool operator <= (const Frac &a, const Frac &b) {
	return 1ll * a.u * b.d <= 1ll * b.u * a.d;
}
ostream& operator << (ostream &o, const Frac &f) {
	o << f.u << "/" << f.d;
	return o;
}

Frac Slope(P &a, P &b) {
	Frac f;
	f.u = b.y - a.y;
	f.d = b.x - a.x;
	f.norm();
	return f;
}