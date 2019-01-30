#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k, l, m;
    cin>>k>>l>>m;
    const int MAX_N = 1000000;
    vector<bool> dp(MAX_N+1, false);
    for (int i = 1; i <= MAX_N; ++i) {
        if (!dp[i-1])
            dp[i] = true;
        if (i >= k && !dp[i-k])
            dp[i] = true;
        if (i >= l && !dp[i-l])
            dp[i] = true;
    }
    while (m--) {
        int n;
        cin>>n;
        cout<<(dp[n] ? "A" : "B");
    }
    cout<<endl;
}
