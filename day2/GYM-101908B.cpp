#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int dp[101][101];
const int MAX_NIMBER = 310;
const int FLAG = 305;
int solve(const int l, const int c) {
    int& ans = dp[l][c];
    if (ans != -1)
        return ans;
    if (l == 0 || c == 0 || l == c)
        return FLAG;
    bitset<MAX_NIMBER+1> reachable;
    for (int u = 1; u <= min(l, c); ++u)
        reachable.set(solve(l-u, c-u));
    for (int u = 1; u <= l; ++u)
        reachable.set(solve(l-u, c));
    for (int u = 1; u <= c; ++u)
        reachable.set(solve(l, c-u));
    for (int x = 0; x <= MAX_NIMBER; ++x)
        if (!reachable.test(x))
            return ans = x;
    throw 42;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(dp, -1, sizeof dp);
    int n;
    cin>>n;
    int nimber = 0;
    for (int i = 0; i < n; ++i) {
        int l, c;
        cin>>l>>c;
        nimber ^= solve(l, c);
    }
    cout<<(nimber ? "Y" : "N")<<endl;
}
