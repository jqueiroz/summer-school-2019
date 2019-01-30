#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    vector<string> v(n);
    for (int i = 0; i < n; ++i)
        cin>>v[i];
    int len = (int)v[n-1].size();
    vector<string> result;
    result.push_back(v[n-1]);
    for (int i = n-2; i >= 0; --i) {
        const int sz1 = (int)v[i].size();
        const int sz2 = min((int)v[i+1].size(), len);
        bool lt = false;
        for (int j = 0; j < sz1; ++j) {
            if (j < sz2)
                lt |= v[i][j] < v[i+1][j];
            if (lt || (j < sz2 && v[i][j] == v[i+1][j])) {
                len = j+1;
            } else {
                break;
            }
        }
        result.push_back(v[i].substr(0, len));
    }
    reverse(result.begin(), result.end());
    for (const string x : result)
        cout<<x<<'\n';
}
