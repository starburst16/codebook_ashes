template <class T, class IndexType1, class IndexType2>
struct FenwickTreeSparse2DOffline {
    int U; vector<int> st, cnt; vector<IndexType1> inds1;
    vector<IndexType2> inds2; vector<T> BIT;
    int getInd1(IndexType1 i) {
        return upper_bound(inds1.begin(), inds1.end(), i) - inds1.begin();
    }
    int getInd2(int i, IndexType2 j) {
        return upper_bound(inds2.begin() + st[i],
            inds2.begin() + st[i] + cnt[i], j)
            - inds2.begin() - st[i];
    }
    FenwickTreeSparse2DOffline(vector<pair<IndexType1, IndexType2>> updateInds)
        : inds1(updateInds.size()) {
        sort(updateInds.begin(), updateInds.end(),
            [&](const pair<IndexType1, IndexType2>& a,
                const pair<IndexType1, IndexType2>& b) {
                    return a.second < b.second;
            });
        for (int i = 0; i < int(updateInds.size()); i++)
            inds1[i] = updateInds[i].first;
        sort(inds1.begin(), inds1.end());
        inds1.erase(unique(inds1.begin(), inds1.end()), inds1.end());
        U = int(inds1.size()); st.assign(U + 1, 0); cnt.assign(U + 1, 0);
        vector<IndexType2> last(U + 1, T()); for (auto&& u : updateInds)
            for (int i = getInd1(u.first); i <= U; i += i & -i)
                if (cnt[i] == 0 || u.second != last[i]) {
                    cnt[i]++; last[i] = u.second;
                }
        for (int i = 1; i <= U; i++) st[i] = st[i - 1] + cnt[i - 1];
        inds2.resize(st[U] + cnt[U]); BIT.resize(st[U] + cnt[U]);
        fill(cnt.begin(), cnt.end(), 0); for (auto&& u : updateInds)
            for (int i = getInd1(u.first); i <= U; i += i & -i)
                if (cnt[i] == 0 || u.second != inds2[st[i] + cnt[i] - 1])
                    inds2[st[i] + cnt[i]++] = u.second;
    }
    void update(IndexType1 i, IndexType2 j, T v) {
        for (int x = getInd1(i); x <= U; x += x & -x)
            for (int s = st[x], c = cnt[x], y = getInd2(x, j); y <= c; y += y & -y)
                BIT[s + y - 1] += v;
    }
    T rsq(IndexType1 d, IndexType2 r) {
        T ret = T(); for (int x = getInd1(d); x > 0; x -= x & -x)
            for (int s = st[x], y = getInd2(x, r); y > 0; y -= y & -y)
                ret += BIT[s + y - 1];
        return ret;
    }
    T rsq(IndexType1 d, IndexType2 l, IndexType2 r) {
        return rsq(d, r) - rsq(d, l - 1);
    }
    T rsq(IndexType1 u, IndexType1 d, IndexType2 l, IndexType2 r) {
        return rsq(d, l, r) - rsq(u - 1, l, r);
    }
};
//Initialize: FenwickTreeSparse2DOffline<ll,int,int> bit(updateInds);
//updateInds: points that will be updated
//Usage: bit.update(x,y,w) or bit.rsq(x_lo, x_hi, y_lo, y_hi);