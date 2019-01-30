#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

const int MAX_N = 100000;
vector<int> adj[MAX_N+1];

double solve(const int u, const int v) {
    double sum = 0;
    int cnt = 0;
    for (const int w : adj[v])
        if (w != u)
            cnt += 1,
            sum += 1 + solve(v, w);
    if (cnt)
        return sum / cnt;
    else
        return 0;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout<<fixed<<setprecision(9)<<solve(-1, 1)<<endl;
}
