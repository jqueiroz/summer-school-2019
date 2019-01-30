#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

long long lcm(long long x, long long y) {
    x /= __gcd(x, y);
    return x*y;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long n, k;
    cin>>n>>k;
    long long mmc = 1;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin>>x;
        x = __gcd(x, k);
        mmc = lcm(mmc, x);
        if (mmc == k) {
            puts("Yes");
            return 0;
        }
    }
    puts("No");
}
