#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <climits>

#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;

vector< pair<int, long long> > g[200002];
int tin[200002], tout[200002], timer;
long long mx[200002][19];
int anc[200002][19];
bool True[200002];
stack< pair < pair<int, int>, pair<long long, bool> > > st;

void dfs(){
    while (!st.empty()){
        pair < pair<int, int>, pair<long long, bool> > q = st.top();
        st.pop();
        int v = q.F.F, prev = q.F.S;
        long long val = q.S.F;
        bool flag = q.S.S;
        if (flag == false){
            tout[v] = timer++;
            continue;
        }
        tin[v] = timer++;
        anc[v][0] = prev;
        mx[v][0] = val;
        for (int i = 1; i < 19; ++i){
            mx[v][i] = max(mx[v][i - 1], mx[anc[v][i - 1]][i - 1]);
            anc[v][i] = anc[anc[v][i - 1]][i - 1];
        }
        st.push(mp(mp(v, prev), mp(val, false)));
        for (int i = 0; i < g[v].size(); ++i){
            if (!True[g[v][i].F]){
                True[g[v][i].F] = true;
                st.push(mp(mp(g[v][i].F, v), mp(g[v][i].S, true)));
            }
        }
    }
}

bool is_ancestor(int a, int b){
    return (tin[a] <= tin[b]) && (tout[a] >= tout[b]);
}

long long query(int a, int b){
    long long res = LLONG_MIN;
    for (int i = 18; i >= 0; --i){
        if (!is_ancestor(anc[a][i], b)){
            res = max(res, mx[a][i]);
            a = anc[a][i];
        }
    }
    if (!is_ancestor(a, b)){
        res = max(res, mx[a][0]);
        a = anc[a][0];
    }
    for (int i = 18; i >= 0; --i){
        if (!is_ancestor(anc[b][i], a)){
            res = max(res, mx[b][i]);
            b = anc[b][i];
        }
    }
    if (!is_ancestor(b, a)){
        res = max(res, mx[b][0]);
        b = anc[b][0];
    }
    return res;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int u, v, n, m;
    cin >> n;
    for (int i = 0; i < n - 1; ++i){
        long long length;
        cin >> u >> v >> length;
        g[u].pb(mp(v, length));
        g[v].pb(mp(u, length));
    }
    st.push(mp(mp(1, 1), mp(0, true)));
    True[1] = true;
    dfs();
    cin >> m;
    if (m == 0){
        cout << endl;
        return 0;
    }
    for (int i = 0; i < m; ++i){
        cin >> u >> v;
        if (u == v){
            cout << 0 << endl;
        } else {
            cout << query(u, v) << endl;
        }
    }
    return 0;
}

