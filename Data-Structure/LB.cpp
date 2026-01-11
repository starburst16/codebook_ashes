vector<ll> p(61);
auto ins = [&](ll x){
    for (int i = 60; i >= 0; i--){
        if (x >> i & 1){
            if (!p[i]){
                p[i] = x;
                break;
            }else{
                x ^= p[i];
            }
        }
    }
};