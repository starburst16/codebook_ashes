// p, q is convex
int sign(double a){
    return fabs(a) < eps ? 0 : a > 0 ? 1 : -1;
}
double PointSegDist(pdd q0, pdd q1, pdd p) {
    if (sign(abs(q0 - q1)) == 0) return abs(q0 - p);
    if (sign(dot(q1 - q0, p - q0)) >= 0 && sign(dot(q0 - q1, p - q1)) >= 0)
        return fabs(cross(q1 - q0, p - q0) / abs(q0 - q1));
    return min(abs(p - q0), abs(p - q1));
}
double TwoConvexHullMinDist(vector<pll> A, vector<pll> B) {
    for (auto& p : B) p = { -p.X, -p.Y };
    vector<pll> C = minkowski(A, B); // assert SZ(C) > 0
    if (PointInConvex(C, pll(0, 0))) return 0;
    double ans = PointSegDist(C.back(), C[0], pll(0, 0));
    for (int i = 0; i + 1 < C.size(); ++i) {
        ans = min(ans, PointSegDist(C[i], C[i + 1], pll(0, 0)));
    }
    return ans;
}