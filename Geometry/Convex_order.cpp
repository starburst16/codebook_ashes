int quard(P p) {
    if (p.x > 0 && p.y >= 0) return 1;
    if (p.x <= 0 && p.y > 0) return 2;
    if (p.x < 0 && p.y <= 0) return 3;
    if (p.x >= 0 && p.y < 0) return 4;
    return -1;
}
P getcenter(vector<P>& p) {
    P res(0, 0); double n = (double)p.size();
    for (P it : p) res.x += it.x, res.y += it.y;
    res.x /= n; res.y /= n;
    return res;
}
void convex_order(vector<P>& p) {
    P center = getcenter(p);
    auto cmp = [&](P a, P b) {
        P tmpa = a - center,tmpb = b - center;
        int qa = quard(tmpa), qb = quard(tmpb);
        if (qa != qb) return qa < qb;
        return (tmpa ^ tmpb) > 0;
    };
    sort(ALL(p), cmp);
}