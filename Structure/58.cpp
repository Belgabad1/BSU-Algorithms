#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <stack>

#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;

int p[111111];
vector < pair<int, int> > a;
stack< pair<int, bool> > st;

int toint(string s){
    int res = 0;
    for (int i = 0; i < s.size(); ++i){
        res = res * 10 + s[i] - 48;
    }
    return res;
}

int find_set(int a){
    st.push(mp(a, true));
    while (!st.empty()){
        pair<int, bool> q = st.top();
        st.pop();
        if (q.S){
            st.push(mp(q.F, false));
            if (q.F != p[q.F]){
                st.push(mp(p[q.F], true));
            }
        } else {
            p[q.F] = p[p[q.F]];
        }
    }
    return p[a];
    /*if (a == p[a]){
        return a;
    } else {
        p[a] = find_set(p[a]);
        return p[a];
    }*/
}

void union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if (a != b){
        p[b] = a;
    }
}

int main(){
    //freopen("input.txt","r",stdin);
    freopen("equal-not-equal.in","r",stdin);
    freopen("equal-not-equal.out","w",stdout);
    ios_base::sync_with_stdio(false);
    int n, m;
    string s1, s2, s3;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i){
        p[i] = i;
    }
    for (int i = 0; i < m; ++i){
        cin >> s1 >> s2 >> s3;
        s1.erase(0, 1);
        s3.erase(0, 1);
        if (s2[0] == '!'){
            a.pb(mp(toint(s1), toint(s3)));
        } else {
            union_set(toint(s1), toint(s3));
        }
    }
    for (int i = 0; i < a.size(); ++i){
        int u = find_set(p[a[i].F]);
        int v = find_set(p[a[i].S]);
        if (u == v){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}
