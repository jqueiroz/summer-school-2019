#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin>>n>>m>>k;
    vector<int> c(k);
    for (int i = 0; i < k; ++i)
        cin>>c[i];
    vector<int> typeof(n+1);
    for (int id = 0, i = 0; i < k; ++i) {
        for (int j = 1; j <= c[i]; ++j)
            typeof[id+j] = i;
        id += c[i];
    }
    const int INF = 1.05e9;
    vector<vector<int>> adj_free(n+1);
    vector<vector<int>> cost(k, vector<int>(k, INF));
    for (int i = 0; i < k; ++i)
        cost[i][i] = 0;
    while (m--) {
        int u, v, x;
        cin>>u>>v>>x;
        const int tu = typeof[u];
        const int tv = typeof[v];
        if (x == 0) {
            adj_free[u].push_back(v);
            adj_free[v].push_back(u);
        }
        cost[tu][tv] = min(cost[tu][tv], x);
        cost[tv][tu] = min(cost[tv][tu], x);
    }
    vector<bool> visited(n+1);
    vector<bool> visitedg(k);
    for (int id = 0, i = 0; i < k; ++i) {
        if (visitedg[i])
            continue;
        queue<int> q;
        q.push(id + 1);
        int cnt = 0;
        while (!q.empty()) {
            const int u = q.front();
            q.pop();
            if (visited[u])
                continue;
            visited[u] = true;
            cnt += 1;
            if (!visitedg[typeof[u]]) {
                visitedg[typeof[u]] = true;
                cnt -= c[typeof[u]];
            }
            for (const int v : adj_free[u])
                if (!visited[v])
                    q.push(v);
        }
        if (cnt != 0) {
            cout<<"No\n";
            return 0;
        }
        id += c[i];
    }
    for (int w = 0; w < k; ++w)
        for (int u = 0; u < k; ++u)
            for (int v = 0; v < k; ++v)
                cost[u][v] = min(cost[u][v], cost[u][w] + cost[w][v]);
    cout<<"Yes\n";
    for (int u = 0; u < k; ++u) {
        for (int v = 0; v < k; ++v)
            cout<<(cost[u][v]==INF ? -1 : cost[u][v])<<' ';
        cout<<"\n";
    }
}
