//can use it to check if line is entirely in polygon
//if line intersect at an edge of polygon => false
//then check midpoint(maybe more points) is in polygon
int ori(pdd a, pdd b, pdd c){
    return sign(cross(b - a, c - a));   
}
bool collinearity(pdd p1, pdd p2, pdd p3){
    return sign(cross(p1 - p3, p2 - p3)) == 0;
}
bool btw(pdd p1, pdd p2, pdd p3) {
    if (!collinearity(p1, p2, p3)) return 0;
    return sign(dot(p1 - p3, p2 - p3)) <= 0;
}
bool PointInConvex(const vector<pll>& C, pll p, bool strict = true) {
    int a = 1, b = SZ(C) - 1, r = !strict;
    if (SZ(C) == 0) return false;
    if (SZ(C) < 3) return r && btw(C[0], C.back(), p);
    if (ori(C[0], C[a], C[b]) > 0) swap(a, b);
    if (ori(C[0], C[a], p) >= r || ori(C[0], C[b], p) <= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (ori(C[0], C[c], p) > 0 ? b : a) = c;
    }
    return ori(C[a], C[b], p) < r;
}
