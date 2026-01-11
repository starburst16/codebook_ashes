const int mod = 1e9 + 7;
vector<long long> fwt(vector<long long> A, bool inv){
  int N = A.size();
  for (int i = 1; i < N; i <<= 1){
    for (int j = 0; j < N; j++){
      if ((j & i) == 0){
        long long x = A[j];
        long long y = A[j | i];
        A[j] = (x + y) % mod;
        A[j | i] = (x - y + mod) % mod;
        if (inv){
          A[j] *= (mod + 1) / 2;
          A[j] %= mod;
          A[j | i] *= (mod + 1) / 2;
          A[j | i] %= mod;
        }
      }
    }
  }
  return A;
}
vector<long long> xor_convolution(vector<long long> A, vector<long long> B){
  int N = A.size();
  A = fwt(A, false);
  B = fwt(B, false);
  vector<long long> C(N);
  for (int i = 0; i < N; i++){
    C[i] = A[i] * B[i] % mod;
  }
  C = fwt(C, true);
  return C;
}