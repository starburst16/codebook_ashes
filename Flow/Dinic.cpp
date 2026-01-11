(a) Bounded Maxflow Construction:
1. add two node ss, tt
2. add_edge(ss, tt, INF)
3. for each edge u -> v with capacity [l, r]:
        add_edge(u, tt, l)
        add_edge(ss, v, l)
        add_edge(u, v, r-l)
4. see (b), check if it is possible.
5. answer is maxflow(ss, tt) + maxflow(s, t)
-------------------------------------------------------
(b) Bounded Possible Flow:
1. same construction method as (a)
2. run maxflow(ss, tt)
3. for every edge connected with ss or tt:
        rule: check if their rest flow is exactly 0
4. answer is possible if every edge do satisfy the rule;
5. otherwise, it is NOT possible.
-------------------------------------------------------
(c) Bounded Minimum Flow:
1. same construction method as (a)
2. answer is maxflow(ss, tt)
-------------------------------------------------------
(d) Bounded Minimum Cost Flow:
* the concept is somewhat like bounded possible flow.
1. same construction method as (a)
2. answer is maxflow(ss, tt) + (∑ l * cost for every edge)
-------------------------------------------------------
(e) Minimum Cut: 
1. run maxflow(s, t)
2. run cut(s)
3. ss[i] = 1: node i is at the same side with s.
-------------------------------------------------------
using T = long long;
struct Edge {
	int to, rev;
	T cap;
	Edge(int a, T b, int c) : to(a), cap(b), rev(c) {}
};
T Flow(vector<vector<Edge>> &g, int s, int t){
	int n = g.size();
	T res = 0;
	vector<int> lev(n, -1), iter(n);
	while(true){
		vector<int> que(1, s);
		fill(lev.begin(), lev.end(), -1);
		fill(iter.begin(), iter.end(), 0);
		lev[s] = 0;
		for (int i = 0; i < (int)que.size(); i++){
			int x = que[i];
			for (Edge &e : g[x]){
				if (e.cap > 0 && lev[e.to] == -1){
					lev[e.to] = lev[x] + 1;
					que.push_back(e.to);
				}
			}
		}
		if (lev[t] == -1) break;
		auto Dfs = [&](auto dfs, int x, T f = 2e18){
			if (x == t) return f;
			T res = 0;
			for (int &i = iter[x]; i < (int)g[x].size(); i++){
				Edge &e = g[x][i];
				if (e.cap > 0 && lev[e.to] == lev[x] + 1){
					T p = dfs(dfs, e.to, min(f - res, e.cap));
					res += p;
					e.cap -= p;
					g[e.to][e.rev].cap += p;
				}
			}
			if (res == 0) lev[x] = -1;
			return res;
		};
		res += Dfs(Dfs, s);
	}
	return res;
}
auto Add = [&](int a, int b, ll c){
  g[a].emplace_back(b, c, (int)g[b].size());
  g[b].emplace_back(a, 0, (int)g[a].size()-1);
};