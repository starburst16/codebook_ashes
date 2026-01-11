vector<int> dfn(n), low(n);
int timer = 0, bcc = 0;
vector<int> id(n, -1);
stack<int> stk;
vector<vector<int>> comp(n);
vector<int> res;
function<void(int, int)> tarjan = [&](int u, int fa){
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    for (int e:adj[u]){
        int v = u ^ a[e] ^ b[e];
        if (v == fa) continue;
        if (!dfn[v]){
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]){
                int z;
                do {
                    z = stk.top();
                    stk.pop();
                    comp[bcc].push_back(z);
                    id[z] = bcc;
                } while (z != v);
                comp[bcc].push_back(u);
                id[u] = bcc++; // id[u] can have multiple values
            }
        }else{
            low[u] = min(low[u], dfn[v]);
        }
    }
};