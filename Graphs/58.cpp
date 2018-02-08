#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <queue>

#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;

const int INF = 1e9 + 7;
int a[55][55];

struct rib {
	int b, u, c, f;
	size_t back;
};

vector <rib> g[2500];

void add_rib (int a, int b) {
	rib r1 = { b, 1, 1, 0, g[b].size() };
	rib r2 = { a, 0, -1, 0, g[a].size() };
	g[a].pb(r1);
	g[b].pb(r2);
}

int main()
{
    //freopen("input.txt","r",stdin);
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
	int n, m, nn = 0;

	int s, t;

	string gg;
    cin >> n >> m;
    for (int i = 0; i < n; ++i){
        cin >> gg;
        for (int j = 0; j < m; ++j){
            if (gg[j] == '*'){
                a[i][j] = -1;
            }
            if (gg[j] == 'M'){
                s = i * m + j;
            }
            if (gg[j] == 'G'){
                t = i * m + j;
            }
            if (a[i][j] == -1){
                continue;
            }
            ++nn;
        }
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            for (int ii = -1; ii < 2; ++ii){
                for (int jj = -1; jj < 2; ++jj){
                    if (i + ii >= 0 && i + ii < n && j + jj >= 0 && j + jj < m && abs(ii) + abs(jj) == 1
                        && a[i + ii][j + jj] != -1 && a[i][j] != -1){
                        add_rib(i * m + j, (i + ii) * m + (j + jj));
                    }
                }
            }
        }
    }
    n = n * m;
	int flow = 0,  cost = 0;
	while (flow < 2) {
		vector<int> dist (n, INF);
		priority_queue< pair<int,int> > q;
		vector<int> prev (n);
		vector<size_t> prev_rib (n);
		q.push(mp(0, s));
		dist[s] = 0;
		while (!q.empty()) {
			int v = q.top().S;
			q.pop();
			for (size_t i = 0; i < g[v].size(); ++i) {
				rib & r = g[v][i];
				if (r.f < r.u && dist[v] + r.c < dist[r.b]) {
					dist[r.b] = dist[v] + r.c;
                    q.push(mp(-dist[r.b], r.b));
					prev[r.b] = v;
					prev_rib[r.b] = i;
				}
			}
		}
		if (dist[t] == INF){
            break;
		}
		int addflow = 2 - flow;
		for (int v = t; v != s; v = prev[v]) {
			int prev_v = prev[v];
			size_t prev_r = prev_rib[v];
			addflow = min (addflow, g[prev_v][prev_r].u - g[prev_v][prev_r].f);
		}
		for (int v = t; v != s; v = prev[v]) {
			int prev_v = prev[v];
            size_t prev_r = prev_rib[v],  r = g[prev_v][prev_r].back;
			g[prev_v][prev_r].f += addflow;
			g[v][r].f -= addflow;
			cost += g[prev_v][prev_r].c * addflow;
		}
		flow += addflow;
	}
	if (flow == 2){
        cout << cost << endl;
	} else {
        cout << -1 << endl;
	}
	return 0;
}
