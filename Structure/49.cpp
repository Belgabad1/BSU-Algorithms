#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 2 * 300001;

int tree[MAXN * 4];

struct line{
    int x, y;
} a[300001];

bool comp(line a, line b){
    return a.x < b.x;
}

void modify(int v, int l, int r, int pos){
    if (l > r){
        return;
    }
    if (l == r){
        tree[v] = 1;
        return;
    }
    int m = (l + r) / 2;
    if (pos <= m){
        modify(v * 2, l, m, pos);
    } else {
        modify(v * 2 + 1, m + 1, r, pos);
    }
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

ll query(int v, int tl, int tr, int l, int r){
    if (l == tl && r == tr){
        return tree[v] * 1LL;
    }
    if (l > r){
        return 0;
    }
    int m = (tl + tr) / 2;
    return query(v * 2, tl, m, l, min(r, m)) + query(v * 2 + 1, m + 1, tr, max(l, m + 1), r);
}

int main(){
    freopen("chords.in", "r", stdin);
    freopen("chords.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> a[i].x >> a[i].y;
        if (a[i].x > a[i].y){
            swap(a[i].x, a[i].y);
        }
    }
    sort(a, a + n, comp);
    ll ans = 0;
    for (int i = 0; i < n; ++i){
        ans += query(1, 0, 2 * n - 1, a[i].x - 1, a[i].y - 1);
        modify(1, 0, 2 * n - 1, a[i].y - 1);
    }
    cout << ans << endl;
    return 0;
}
