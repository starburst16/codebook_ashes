typedef complex<double> cd;
void fft(vector<cd> &a)
{
    int n=a.size(),L=31-__builtin_clz(n);
    vector<int> rev(n);
    for(int i=0;i<n;i++) rev[i]=(rev[i/2]+((i&1)<<L))/2;
    for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    static vector<complex<long double>> R(2,1);
    static vector<cd> rt(2,1);
    for(static int k=2;k<n;k*=2)
    {
        R.resize(n); rt.resize(n);
        auto z=polar(1.0L,acos(-1.0L)/k);
        for(int i=k;i<2*k;i++) rt[i]=R[i]=R[i/2]*((i&1)?z:1);
    }
    for(int k=1;k<n;k*=2)
    {
        for(int i=0;i<n;i+=2*k)
        {
            for(int j=0;j<k;j++)
            {
                cd z=rt[j+k]*a[i+j+k];
                a[i+j+k]=a[i+j]-z;
                a[i+j]+=z;
            }
        }
    }
}

template<ll mod> vector<ll> mul_mod(vector<ll> &a,vector<ll> &b)
{
    int sa=a.size(),sb=b.size();
    if(sa==0||sb==0) return {};
    int n=1<<(32-__builtin_clz(sa+sb-2)),S=(1<<15);
    vector<cd> f(n),g(n),hs(n),hl(n);
    for(int i=0;i<sa;i++) f[i]=cd(a[i]&(S-1),(a[i]>>15));
    for(int i=0;i<sb;i++) g[i]=cd(b[i]&(S-1),(b[i]>>15));
    fft(f); fft(g);
    for(int i=0;i<n;i++)
    {
        int j=(-i)&(n-1);
        hs[i]=(f[j]+conj(f[i]))*g[j]/(2.0*n);
        hl[i]=(f[j]-conj(f[i]))*conj(g[i])/(2.0*n);
    }
    fft(hs); fft(hl);
    vector<ll> c(sa+sb-1);
    for(int i=0;i<sa+sb-1;i++)
    {
        ll ah=ll(real(hl[i])+0.5),ch=ll(real(hs[i])+0.5);
        ll bh=ll(imag(hl[i])+0.5)+ll(imag(hs[i])+0.5);
        c[i]=((ah%mod*S+bh)%mod*S+ch)%mod;
    }
    return c;
}