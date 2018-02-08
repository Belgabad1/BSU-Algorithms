#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <memory.h>
#include <algorithm>

#define F first
#define S second
#define pb push_back
#define mp make_pair

using namespace std;

vector<int> w[400];
int cur[400];
long long iter, iter1;
int ox[4] = {-1, 0, 0, 1};
int ind[20];
int oy[4] = {0, -1, 1, 0};
const int maxN = 550000;
int a[20], k = 1, step;
int bt[maxN + 1], revv[maxN + 1];
int n;
int symm, asymm;
vector< vector<int> > st;
map< vector<int>, bool> m;
vector<int> numbers[20];
vector<int> mas;
int first = 1;
int two[20];
bool b[20][20];
vector< pair<int, int> > el;
int current;

int True[20];

bool comp(int a, int b) {
    return bt[a] < bt[b];
}

void print(vector<int> a) {
    int step = a.size(), mn = 22, mx = 0;
    int b[20][20];
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            b[i][j] = false;
        }
    }
    for (int i = step - 1; i >= 0; --i) {
        int j = a[i], k = 0;
        bool True = false;
        while (j){
            if (!True && j % 2 == 1) {
                mn = min(mn, k);
            }
            b[step - i - 1][k++] = j % 2;
            j /= 2;
        }
        mx = max(mx, k);
    }
    for (int i = step - 1; i >= 0; --i) {
        for (int j = mn; j < mx; ++j) {
            if (b[i][j]) {
                cout <<'#';
            } else {
                cout << '_';
            }
        }
        cout << endl;
    }
    cout << endl;
}

int rev_num(int x) {
    int a[20];
    memset(a, 0, sizeof a);
    int cur = 0;
    while (x) {
        a[cur++] = x % 2;
        x /= 2;
    }
    int res = 0;
    for (int i = 0; i < n + 1 - n % 2; ++i) {
        res *= 2;
        res += a[i];
    }
    return res;
}

void check(int sum) {
    a[step++] = first;
    vector<int> rev;
    for (int i = 0; i < step; ++i) {
        rev.pb(revv[a[i]]);
        if (a[i] != rev[i]) {
            ++asymm;
            if (st.size() < 10000 && a[i] > rev[i]) {
                ++i;
                while(i < step) {
                    rev.pb(revv[a[i]]);
                    ++i;
                }
                st.pb(rev);
            }
            --step;
            return;
        }
    }
    ++symm;
    if (st.size() < 10000) {
        st.pb(rev);
    }
    --step;
}

void broot(int blocks, int sum = n / 2 + 1) {
    if (blocks == n) {
        if (sum % n != 0) {
            return;
        }
        if (!(sum / n == n / 2 + 1)) {
            return;
        }
        step = 0;
        for (int i = n; i >= 0; --i) {
            if (ind[i] != 0) {
                a[step++] = ind[i];
            }
        }
        check(sum);
        return;
    }
    if (!(sum / n <= n / 2 && (sum + n * (n - blocks)) / n >= n / 2)) {
        return;
    }
    if (blocks == n - 1 && ((n / 2 + 1) * n - sum - 1 < 0 | (n / 2 + 1) * n - sum - 1 > n + 1 - n % 2)) {
            return;
    }
    int q = current;
    int Save[20];
    for (int i = 0; i < n; ++i) {
        Save[i] = True[i];
    }
    for (; current < el.size(); ++current) {
        int x = el[current].F, y = el[current].S;
        int u = x * 20 + y;
        int pp = cur[u];
        for (; cur[u] < w[u].size(); ++cur[u]){
            if (!(True[x + ox[w[u][cur[u]]]] & two[n - n % 2 - y - oy[w[u][cur[u]]]])) {
                int xx = x + ox[w[u][cur[u]]], yy = y + oy[w[u][cur[u]]];
                True[xx] |= two[n - n % 2 - yy];
                el.pb(mp(xx, yy));
                ind[xx] |= two[n - n % 2 - yy];
                broot(blocks + 1, sum + yy + 1);
                ind[xx] ^= two[n - n % 2 - yy];
                el.pop_back();
            }
        }
        cur[u] = pp;
    }
    for (int i = 0; i < n; ++i) {
        True[i] = Save[i];
    }
    current = q;
}

int main() {
    freopen("polyomino.in", "r", stdin);
    freopen("polyomino.out", "w", stdout);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> n;
    int k = 1;
    two[0] = 1;
    for (int i = 1; i < 20; ++i) {
        two[i] = two[i - 1] * 2;
    }
    for (int i = 0; i < n / 2; ++i) {
        first *= 2;
    }
    for (int i = 0; i < n + 1 - n % 2; ++i) {
        k *= 2;
    }
    for (int i = 1; i <= k; ++i) {
        revv[i] = rev_num(i);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (i + ox[k] >= 0 && i + ox[k] < n && j + oy[k] >= 1 - n % 2 && j + oy[k] < n) {
                    if (!(i + ox[k] == 0 && j + oy[k] == n / 2)) {
                        w[i * 20 + j].pb(k);
                    }
                }
            }
        }
    }
    True[0] |= two[n - n % 2 - n / 2];
    ind[0] |= two[n / 2];
    el.pb(mp(0, n / 2));
    broot(1);
    cout << symm + asymm / 2 << endl;
    vector< vector<int> >::iterator it = st.begin();
    int cnt = 0;
    for (; it != st.end(); ++it) {
        print(*it);
        ++cnt;
        if (cnt == 10000){
            break;
        }
    }
    return 0;
}
