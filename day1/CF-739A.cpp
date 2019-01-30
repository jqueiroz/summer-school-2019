#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    int len = 1e9;
    while (m--) {
        int l, r;
        cin>>l>>r;
        len = min(len, r-l+1);
    }
    cout<<len<<endl;
    for (int i = 0; i < n; ++i)
        cout<<i%len<<' ';
    cout<<endl;
}
