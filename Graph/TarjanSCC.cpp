割點
點 u 為割點 if and only if 滿足 1. or 2. 
1. u 爲樹根，且 u 有多於一個子樹。 
2. u 不爲樹根，且滿足存在 (u,v) 爲樹枝邊 (或稱父子邊，即 u 爲 v 在搜索樹中的父親)，使得 DFN(u) <= Low(v)。

-------------------------------------------------------
橋
一條無向邊 (u,v) 是橋 if and only if (u,v) 爲樹枝邊，且滿足 DFN(u) < Low(v)。

vector<int> dfn(n), low(n), ins(n);
int timer = 0, scc = 0;
vector<int> id(n);
stack<int> stk;
void tarjan(int u){
  low[u] = dfn[u] = ++timer;
  ins[u] = 1;
  stk.push(u);
  for (int v:adj[u]){
    if (!dfn[v]){
      tarjan(v);
      low[u] = min(low[u], low[v]);
    }else if (ins[v]){
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]){
    int v;
    do {
      v = stk.top(); stk.pop();
      id[v] = scc;
      ins[v] = 0;
    } while(v != u);
    scc++;
  }
}
