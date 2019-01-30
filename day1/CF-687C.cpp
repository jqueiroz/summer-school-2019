#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    bitset<501> dp[501];
    dp[0].set(0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin>>x;
        for (int v = 500; v >= x; --v) {
            dp[v] |= dp[v-x];
            dp[v] |= dp[v-x] << x;
        }
    }

    cout<<dp[k].count()<<endl;
    for (int v = 0; v <= 500; ++v)
        if (dp[k][v])
            cout<<v<<' ';
    cout<<endl;
}
