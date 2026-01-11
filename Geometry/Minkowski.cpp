void reorder_polygon(vector<P>& P) {
    size_t pos = 0;
    for (size_t i = 1; i < P.size(); i++) {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}
vector<P> minkowski(vector<P> p, vector<P> q) {
    // the first vertex must be the lowest
    reorder_polygon(p);
    reorder_polygon(q);
    // we must ensure cyclic indexing
    p.push_back(p[0]);
    p.push_back(p[1]);
    q.push_back(q[0]);
    q.push_back(q[1]);
    // main part
    vector<P> result;
    size_t i = 0, j = 0;
    while (i < p.size() - 2 || j < q.size() - 2) {
        result.push_back(p[i] + q[j]);
        auto cross = (p[i + 1] - p[i]) ^ (q[j + 1] - q[j]);
        if (cross >= 0 && i < p.size() - 2) ++i;
        if (cross <= 0 && j < q.size() - 2) ++j;
    }
    return result;
}