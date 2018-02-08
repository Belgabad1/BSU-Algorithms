#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>

#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef long long ll;

using namespace std;

queue< pair< pair<int, int>, pair<int, int> > > q;
int dp[1002][1002];
pair<int, pair<int, int> > data[1002][1002];
int a[1002][1002];
vector< pair<int, pair<int, int> > > edges[1000001];
int num[1010002], cur;
vector< pair<int, int> > answer;
int mincost[1000001];

int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    int n, r, f, b, l[1002], xf = -1, yf = -1;
    cin >> n >> r;
    for (int i = 1; i <= n; ++i){
        mincost[i] = INT_MAX;
    }
    cin >> f >> b;
    int mx = 0;
    for (int i = 0; i < r; ++i){
        cin >> l[i];
        mx = max(mx, l[i]);
        for (int j = 0; j < l[i]; ++j){
            cin >> a[i][j];
            if (a[i][j] == b){
                q.push(mp(mp(0,b), mp(i, j)));
                dp[i][j] = 0;
                ++num[0];
            } else {
                dp[i][j] = INT_MAX;
            }
            if (j > 0){
                if (a[i][j] != b && a[i][j] != f && a[i][j - 1] != b){
                    edges[a[i][j]].pb(mp(a[i][j - 1], mp(i, j - 1)));
                }
                if (a[i][j] != b && a[i][j - 1] != f && a[i][j - 1] != b){
                    edges[a[i][j - 1]].pb(mp(a[i][j], mp(i, j)));
                }
            }
        }
    }
    mincost[b] = 0;
    if (f == b){
        cout << 0 << endl;
        return 0;
    }
    if (mx <= 1){
        cout << "NoWay" << endl;
        return 0;
    }
    int mn = INT_MAX;
    while (!q.empty()){
        pair< pair<int, int>, pair<int, int> > d = q.front();
        q.pop();
        int len = d.F.F, v = d.F.S, route = d.S.F, stay = d.S.S;
        if (dp[route][stay] < len){
            --num[len];
            continue;
        }
        if (len > cur){
            q.push(d);
            continue;
        }
        --num[len];
        int newval = dp[route][stay] + 4;
        if (mincost[v] > dp[route][stay]){
            for (int i = 0; i < (int)edges[v].size(); ++i){
                pair<int, pair<int, int> > ver = edges[v][i];
                if (ver.S.F != route || abs(ver.S.S - stay) != 1){
                    if (dp[ver.S.F][ver.S.S] > newval){
                        dp[ver.S.F][ver.S.S] = newval;
                        ++num[dp[ver.S.F][ver.S.S]];
                        q.push(mp(mp(dp[ver.S.F][ver.S.S], ver.F), mp(ver.S.F, ver.S.S)));
                        data[ver.S.F][ver.S.S] = mp(v, mp(route, stay));
                    }
                }
            }
        }
        newval -= 3;
        if (stay > 0){
            if (dp[route][stay - 1] > newval){
                dp[route][stay - 1] = newval;
                ++num[dp[route][stay - 1]];
                q.push(mp(mp(dp[route][stay - 1], a[route][stay - 1]), mp(route, stay - 1)));
                data[route][stay - 1] = mp(v, mp(route, stay));
            }
        }
        if (stay < l[route] - 1){
            if (dp[route][stay + 1] > newval){
                dp[route][stay + 1] = newval;
                ++num[dp[route][stay + 1]];
                q.push(mp(mp(dp[route][stay + 1], a[route][stay + 1]), mp(route, stay + 1)));
                data[route][stay + 1] = mp(v, mp(route, stay));
            }
        }
        mincost[v] = min(mincost[v], dp[route][stay]);
        if (num[cur] == 0 && !q.empty()){
            while (num[cur] == 0){
                ++cur;
            }
        }
        if (a[route][stay] == f && dp[route][stay] < mn){
            xf = route;
            yf = stay;
            mn = dp[route][stay];
        }
    }
    if (mn == INT_MAX){
        cout << "NoWay" << endl;
    } else {
        cout << mn << endl;
        while (f != 0){
            answer.pb(mp(f, xf + 1));
            pair<int, pair<int, int> > d = data[xf][yf];
            f = d.F;
            xf = d.S.F;
            yf = d.S.S;
        }
        for (int i = (int)answer.size() - 1; i >= 0; --i){
            if (i == 0 || i == (int)answer.size() - 1){
                cout << answer[i].F << " " << answer[i].S << endl;
            } else {
                cout << answer[i].F << " " << answer[i - 1].S << endl;
            }
        }
    }
    return 0;
}
