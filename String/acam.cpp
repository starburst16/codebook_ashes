const int M = 300005;
struct acam {
    struct node {
        int fail;
        int ch[26] = { 0 };
    }tr[M];
    int cnt = 0;
    map<int, int>ref;
    vector<int>g[M];//par: node.fail -> child: node
    int ans[M];
    void insert(string& s, int id) {
        int u = 0;
        for (char c : s) {
            if (!tr[u].ch[c - 'a']) {
                tr[u].ch[c - 'a'] = ++cnt;
            }
            u = tr[u].ch[c - 'a'];
        }
        ref[id] = u;
    }
    void build() {
        queue<int>que;
        for (int i = 0; i < 26; i++)
            if (tr[0].ch[i])que.push(tr[0].ch[i]);
        while (que.size()) {
            int u = que.front(); que.pop();
            for (int i = 0; i < 26; i++) {
                if (tr[u].ch[i]) {
                    tr[tr[u].ch[i]].fail = tr[tr[u].fail].ch[i];
                    que.push(tr[u].ch[i]);
                }
                else tr[u].ch[i] = tr[tr[u].fail].ch[i];
            }
        }
        for (int i = 1; i <= cnt; i++)
            g[tr[i].fail].push_back(i);
    }

    void query(string& S) {
        int u = 0;
        for (char c : S) {
            u = tr[u].ch[c - 'a'];
            ans[u]++;
        }
    }
    void get_ans() {
        dfs(0);
    }
    void dfs(int u) {
        for (int v : g[u]) {
            dfs(v);
            ans[u] += ans[v];
        }
    }

}trie;
int n;
string T[M], S;
void slove() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> T[i];
        trie.insert(T[i], i);
    }
    trie.build();
    cin >> S;
    trie.query(S);
    trie.get_ans();
    for (int i = 1; i <= n; i++) {
        cout << trie.ans[trie.ref[i]] << endl;
    }
}
