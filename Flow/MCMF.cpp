typedef long long ll;
typedef vector<int> vi;
#define F0R(i, a) for (int i=0; i<(a); i++)
#define trav(a,x) for (auto& a : x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

struct MCMF { 
	using F = ll; using C = ll; // flow type, cost type
	struct Edge { int to; F flo, cap; C cost; };
	int N; 
	vector<C> p, dist; 
	vi pre; 
	vector<Edge> eds;
	vector<vi> adj;
	void init(int _N) { N = _N;
		p.resize(N), dist.resize(N), pre.resize(N), adj.resize(N); }
	void ae(int u, int v, F cap, C cost) { 
		assert(cap >= 0); 
		adj[u].pb(sz(eds)); eds.pb({v,0,cap,cost}); 
		adj[v].pb(sz(eds)); eds.pb({u,0,0,-cost});
	} 
	bool path(int s, int t) { 
		const C inf = numeric_limits<C>::max(); F0R(i,N) dist[i] = inf;
		using T = pair<C,int>; 
		priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({dist[s] = 0,s}); 
		while (sz(todo)) { 
			T x = todo.top(); todo.pop(); 
			if (x.f > dist[x.s]) continue;
			for(auto &e:adj[x.s]) { const Edge& E = eds[e]; 
				if (E.flo < E.cap && ckmin(dist[E.to],x.f+E.cost+p[x.s]-p[E.to]))
					pre[E.to] = e, todo.push({dist[E.to],E.to});
			}
		} 
		return dist[t] != inf;
	}
	pair<F,C> calc(int s, int t) { 
		assert(s != t);
		F0R(_,N) F0R(e,sz(eds)) { 
			const Edge& E = eds[e]; 
			if (E.cap) ckmin(p[E.to],p[eds[e^1].to]+E.cost); }
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { 
			F0R(i,N) p[i] += dist[i]; 
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = eds[pre[x]^1].to) {
				const Edge& E = eds[pre[x]]; ckmin(df,E.cap-E.flo); }
			totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = eds[pre[x]^1].to)
				eds[pre[x]].flo += df, eds[pre[x]^1].flo -= df;
		} 
		return {totFlow,totCost};
	}
};
