#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
using namespace std;
#define DBG(x)   cout << (#x " = ") << x << endl;
#define ALL(x) x.begin(), x.end()
#define push_back emplace_back
#define spIO ios::sync_with_stdio(false);cin.tie(0)
#define mem(arr, value) memset(arr, value, sizeof(arr))
#define for0(i, n) for(int i = 0; i < n; i++)
#define for1(i, n) for(int i = 1; i <= n; i++)
typedef long long ll;
typedef long double ld;
const ll mod = 1e9 + 7;
inline ll pow2(ll target, ll p, ll MOD = mod)
{
    ll ret = 1;
    while (p)
    {
        if (p & 1)
            (ret *= target) %= MOD;
        p >>= 1;
        (target *= target) %= MOD;
    }
    return ret;
}
inline ll inv(ll x, ll MOD = mod)
{
    return pow2(x, MOD - 2, MOD);
}
inline ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    if ((x & 1) && (y & 1))
    {
        if (x < y)
            swap(x, y);
        return gcd(y, x - y);
    }
    if (x & 1)
        return gcd(x, y >> 1);
    if (y & 1)
        return gcd(y, x >> 1);
    return 2 * gcd(x >> 1, y >> 1);
}
inline ll sub(ll x, ll y, ll MOD = mod)
{
    return (x - y < 0 ? x - y + MOD : x - y);
}
inline ll add(ll x, ll y, ll MOD = mod)
{
    return (x + y >= MOD ? x + y - MOD : x + y);
}
vector<pair<int, int>> directions = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };