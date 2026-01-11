vector<int> dfn(n), low(n);
int timer = 0, bcc = 0;
vector<int> id(n);
stack<int> stk;
function<void(int, int)> tarjan = [&](int u, int fa){
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    for (auto e:adj[u]){
        int v = e.first;
        int w = e.second;
        if (w == fa) continue;
        if (!dfn[v]){
            tarjan(v, w);
            low[u] = min(low[u], low[v]);
        }else{
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]){
        while (true) {    
            int v = stk.top();    
			stk.pop();    
            id[v] = bcc;    
            if (v == u) break;    
        }    
        bcc++; 
    }
};