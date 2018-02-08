#include <iostream>
#include <cstdio>
#include <string>
#include <set>
#include <vector>
#include <memory.h>
#include <map>

#define pb push_back

using namespace std;

int ind[26] = {2, 2, 2, 3, 3, 3, 4, 4, 1, 1, 5, 5, 6, 6, 0, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};
int n;
string s, g[50001];
string answer[100001];
int words[100001];
int dp[100001];

struct vertex{
    int next[10];
    int num;
};

vertex t[5000001];
int dim = 0;

void init(){
    memset(t[0].next, 0, sizeof t[0].next);
    t[0].num = -1;
}

void add_string(string s, int num){
    int cur = 0;
    for (int i = 0; i < s.size(); ++i){
        char c = s[i] > 64 ? ind[s[i] - 65] + 48 : s[i];
        if (t[cur].next[c - '0'] != 0){
            cur = t[cur].next[c - '0'];
        } else {
            memset(t[dim + 1].next, 0, sizeof t[dim + 1].next);
            t[dim + 1].num = -1;
            t[cur].next[c - '0'] = dim + 1;
            cur = ++dim;
        }
    }
    t[cur].num = num;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> s;
    for(int i = 0; i <= s.size(); ++i){
        dp[i] = 200000;
    }
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> g[i];
    }
    init();
    for (int i = 0; i < n; ++i){
        add_string(g[i], i);
    }
    dp[0] = 0;
    for (int i = 0; i < s.size(); ++i){
        int j = 1;
        int q = 0;
        while (t[q].next[s[i + j - 1] - '0'] != 0){
            q = t[q].next[s[i + j - 1] - '0'];
            if (t[q].num != -1){
                if (dp[i + j] > dp[i] + 1){
                    dp[i + j] = dp[i] + 1;
                    words[i + j] = t[q].num;
                }
            }
            ++j;
            if (i + j - 1 == s.size()){
                break;
            }
        }
    }

    if (dp[s.size()] > 111111){
        cout << "No solution";
        return 0;
    }
    int i = s.size(), cur = 0;
    while (i != 0){
        answer[cur] = g[words[i]];
        ++cur;
        i -= g[words[i]].size();
    }
    cout << cur << endl;
    for (int i = cur - 1; i >= 0; --i){
        cout << answer[i] << " ";
    }
    return 0;
}
