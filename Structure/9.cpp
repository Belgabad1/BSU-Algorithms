#include <iostream>
#include <cstdio>
#include <climits>
#include <queue>
#include <set>

#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;

typedef long long ll;

ll dp[5000][5000];
priority_queue< pair<int, int> > q;
int n, m;
int ox[4] = {1, 0, 0, -1};
int oy[4] = {0, 1, -1, 0};
ll a[5000][5000];
bool True[5000][5000];
ll ans = 0, h;
bool is[5000][5000];

void dfs(int x, int y){
    True[x][y] = true;
    ans += dp[x][y] - a[x][y];
    for (int i = 0; i < 4; ++i){
        if (x + ox[i] > 0 && x + ox[i] < n - 1 && y + oy[i] > 0 && y + oy[i] < m - 1){
            if (!True[x + ox[i]][y + oy[i]] && a[x + ox[i]][y + oy[i]] <= dp[x][y]){
                dfs(x + ox[i], y + oy[i]);
            }
        }
    }
}

void dijkstra() {
    while (!q.empty()) {
        int v = q.top().S, len = -q.top().F;
        q.pop();
        int x = v / m, y = v % m;
        if (dp[x][y] < len) {
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            if (x + ox[i] > 0 && x + ox[i] < n - 1 && y + oy[i] > 0 && y + oy[i] < m - 1) {
                if (dp[x + ox[i]][y + oy[i]] < dp[x][y] && !is[x + ox[i]][y + oy[i]]){
                    is[x + ox[i]][y + oy[i]] = true;
                    dp[x + ox[i]][y + oy[i]] = dp[x][y];
                    q.push(mp(-dp[x + ox[i]][y + oy[i]], (x + ox[i]) * m + y + oy[i]));
                } else if (dp[x + ox[i]][y + oy[i]] >= dp[x][y]) {
                    ll res = max(dp[x][y], a[x + ox[i]][y + oy[i]]);
                    dp[x + ox[i]][y + oy[i]] = res;
                    if (!is[x + ox[i]][y + oy[i]]) {
                        q.push(mp(-res, (x + ox[i]) * m + y + oy[i]));
                    }
                    is[x + ox[i]][y + oy[i]] = true;
                }
            }
        }
    }
}

int main(){
    //freopen("input.txt", "r", stdin);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ll x, y, v;
    cin >> n >> m;
    cin >> x >> y >> v;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> a[i][j];
            dp[i][j] = a[i][j];
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1){
                is[i][j] = true;
                q.push(mp(-dp[i][j], i * m + j));
            }
        }
    }
    dijkstra();
    h = dp[x - 1][y - 1];
    dfs(x - 1, y - 1);
    cout << min(ans, v) << endl;
    return 0;
}
