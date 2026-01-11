
constexpr int kMod = 998244353;
constexpr int kN = 1<<20;
constexpr int kRoot = 3;
constexpr int kP = kMod;
 
int fpow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) {
      res = 1LL * res * a % kP;
    }
    a = 1LL * a * a % kP;
    n >>= 1;
  }
  return res;
}
 
namespace NTT {
 
vector<int> omega;
void Init() {
  omega.resize(kN + 1);
  long long x = fpow(kRoot, (kMod - 1) / kN);
  omega[0] = 1;
  for (int i = 1; i <= kN; ++i) {
    omega[i] = 1LL * omega[i - 1] * x % kMod;
  }
}
 
void BitReverse(vector<int> &v, int n) {
  int z = __builtin_ctz(n) - 1;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    for (int j = 0; (1 << j) < n; ++j) {
      x ^= (i >> j & 1) << (z - j);
    }
    if (x > i) {
      swap(v[x], v[i]);
    }
  }
}
 
void Transform(vector<int> &v, int n) {
  BitReverse(v, n);
  for (int s = 2; s <= n; s <<= 1) {
    int z = s >> 1;
    for (int i = 0; i < n; i += s) {
      for (int k = 0; k < z; ++k) {
        int x = 1LL * v[i + k + z] * omega[kN / s * k] % kMod;
        v[i + k + z] = (v[i + k] + kMod - x) % kMod;
        (v[i + k] += x) %= kMod;
      }
    }
  }
}
 
void InverseTransform(vector<int> &v, int n) {
  Transform(v, n);
  for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
  const int kInv = fpow(n, kMod - 2);
  for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * kInv % kMod;
}
 
vector<int> Multiply(vector<int> a, vector<int> b) {
  int n = a.size(), m = b.size();
  int s = 1;
  while (s < n + m - 1) {
    s <<= 1;
  }
  a.resize(s);
  b.resize(s);
  Transform(a, s);
  Transform(b, s);
  for (int i = 0; i < s; ++i) {
    a[i] = 1LL * a[i] * b[i] % kP;
  }
  InverseTransform(a, s);
  a.resize(n + m - 1);
  return a;
}
}  // namespace NTT

// remember to call NNT::Init()
// check kN >= n + m && kN = 2 ^ p
