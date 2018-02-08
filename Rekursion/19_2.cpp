#include <iostream>
#include <cstdio>
#include <climits>

#define mp make_pair
#define F first
#define S second

using namespace std;

typedef long long ll;

pair<ll, ll> answer[5010];
ll a[5010];

int main(){
    //freopen("input.txt", "r", stdin);
    freopen("concert.in", "r", stdin);
    freopen("concert.out", "w", stdout);
    ll n, m, d;
    cin >> n >> m >> d;
    m = min(n, m);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i){
        answer[i] = mp(LLONG_MAX, LLONG_MAX);
    }
    answer[0] = mp(1, 0);
    for (int i = 0; i < n; ++i){
        if (a[i] > d){
            continue;
        }
        for (int j = i + 1; j >= 1; --j){
            if (answer[j - 1].F == LLONG_MAX){
                continue;
            }
            ll sum = answer[j - 1].F, cost = answer[j - 1].S;
            if (a[i] <= d - cost){
                cost += a[i];
            } else {
                ++sum;
                cost = a[i];
            }
            if (sum > m){
                continue;
            }
            if ((sum < answer[j].F) || (sum == answer[j].F && cost < answer[j].S)){
                answer[j] = mp(sum, cost);
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i){
        if (answer[i].F != LLONG_MAX){
            ans = i;
        } else {
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
