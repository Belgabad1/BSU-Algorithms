#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

#define mp make_pair
#define pb push_back
#define F first
#define S second

using namespace std;

vector< pair<long double, pair<int, int> > > ribs;
vector<int> g[3000];
vector<int> comp[3000];
int parent[3000], cur, x[3000], y[3000];
bool True[3000];
long double ans;

void dfs(int v) {
    True[v] = true;
    comp[cur].pb(v);
    for (int i = 0; i < g[v].size(); ++i) {
        if (!True[g[v][i]]) {
            dfs(g[v][i]);
        }
    }
}

long double get_dist(int x1, int y1, int x2, int y2) {
    return sqrt(1.*((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

int get_parent(int v) {
    if (v == parent[v]) {
        return parent[v];
    } else {
        parent[v] = get_parent(parent[v]);
        return parent[v];
    }
}

void unite_sets(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a != b) {
        parent[b] = a;
    }
}

long double calc_len() {
    long double res = 0;
    for (int i = 0; i < cur; ++i) {
        if (comp[i].size() > 1) {
            comp[i].pb(comp[i][0]);
        }
        for (int j = 1; j < comp[i].size(); ++j) {
            res += get_dist(x[comp[i][j - 1]], y[comp[i][j - 1]], x[comp[i][j]], y[comp[i][j]]);
        }
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        for (int j = 0; j < i; ++j) {
            ribs.pb(mp(get_dist(x[i], y[i], x[j], y[j]), mp(i, j)));
        }
    }
    int comps = n;
    sort(ribs.begin(), ribs.end());
    for (int i = 0; i < ribs.size(); ++i) {
        if (comps <= m) {
            break;
        }
        int len = ribs[i].F;
        int u = ribs[i].S.F;
        int v = ribs[i].S.S;
        if (get_parent(u) != get_parent(v)) {
            unite_sets(u, v);
            g[u].pb(v);
            g[v].pb(u);
            --comps;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!True[i]) {
            dfs(i);
            ++cur;
        }
    }
    long double answer = calc_len();
    cout << fixed << setprecision(5) << answer << endl;
    for (int i = 0; i < cur; ++i) {
        if (comp[i].size() == 0) {
            cout << 0 << endl;
            continue;
        }
        if (comp[i].size() > 1) {
            cout << comp[i].size() - 1 << " ";
        } else {
            cout << comp[i].size() << " ";
        }
        for (int j = 0; j < comp[i].size(); ++j) {
            if (j != comp[i].size() - 1) {
                cout << comp[i][j] + 1 << " ";
            } else {
                cout << comp[i][j] + 1 << endl;
            }
        }
    }
    for (int i = cur; i < m; ++i) {
        cout << 0 << endl;
    }
    return 0;
}
