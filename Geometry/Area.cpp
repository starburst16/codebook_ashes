double area(const vector<P>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        P p = i ? fig[i - 1] : fig.back();
        P q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}