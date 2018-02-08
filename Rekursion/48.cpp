#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
#include <stack>

#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;

vector<int> g[111111];
int dp[111111][2];
bool True[111111];
stack< pair<int, pair<int, bool> > > st;

void dfs(){
    while (!st.empty()){
        pair<int, pair<int, bool> > q = st.top();
        st.pop();
        int v = q.F, prev = q.S.F;
        bool flag = q.S.S;
        if (flag == false){
            if (g[v].size() == 1 && v != 1){
                dp[v][1] = 1;
                dp[v][0] = 0;
                continue;
            }
            dp[v][1] = 1;
            int mn = INT_MAX;
            int pos = -1;
            bool mn1 = false;
            for (int i = 0; i < g[v].size(); ++i){
                if (g[v][i] == prev){
                    continue;
                }
                if (dp[g[v][i]][1] - dp[g[v][i]][0] < mn && dp[g[v][i]][1] > dp[g[v][i]][0]){
                    mn = dp[g[v][i]][1];
                    pos = i;
                }
                if (dp[g[v][i]][1] < dp[g[v][i]][0]){
                    mn1 = true;
                }
                dp[v][1] += min(dp[g[v][i]][0], dp[g[v][i]][1]);
            }
            for (int i = 0; i < g[v].size(); ++i){
                if (i == pos && !mn1){
                    dp[v][0] += dp[g[v][i]][1];
                } else {
                    dp[v][0] += min(dp[g[v][i]][1], dp[g[v][i]][0]);
                }
            }
        } else {
            True[v] = true;
            st.push(mp(v, mp(prev, false)));
            for (int i = 0; i < g[v].size(); ++i){
                if (!True[g[v][i]]){
                    True[g[v][i]] = true;
                    st.push(mp(g[v][i], mp(v, true)));
                }
            }
        }
    }
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n, l, x;
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> l;
        for (int j = 0; j < l; ++j){
            cin >> x;
            g[i + 1].pb(x);
        }
    }
    for (int i = 0; i < 111111; ++i){
        dp[i][1] = INT_MAX;
    }
    st.push(mp(1, mp(0, true)));
    dfs();
    cout << min(dp[1][0], dp[1][1]) << endl;
    return 0;
}
