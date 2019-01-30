#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200000;
const int MIN_COORD = -1e8;
const int MAX_COORD = +1e8;

vector<vector<pair<int*, int>>> rollback;
int uf[MAX_N+1], sz[MAX_N+1];
int vmin[MAX_N+1][4], vmax[MAX_N+1][4];

int find(int x) {
    if (uf[x] == x)
        return x;
    else
        return find(uf[x]);
}

int query(int u, int v) {
    u = find(u);
    v = find(v);
    int ans = 0;
    for (int i = 0; i < 4; ++i) {
        ans = max(ans, vmax[u][i] - vmin[v][i]);
        ans = max(ans, vmax[v][i] - vmin[u][i]);
    }
    return ans;
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (sz[u] > sz[v]) swap(u, v); // v becomes the new root
    vector<pair<int*, int>> assignments;
    assignments.emplace_back(uf+u, u);
    assignments.emplace_back(sz+v, sz[v]);
    uf[u] = v;
    sz[v] += sz[u];
    for (int i = 0; i < 4; ++i) {
        if (vmin[u][i] < vmin[v][i]) {
            assignments.emplace_back(&vmin[v][i], vmin[v][i]);
            vmin[v][i] = vmin[u][i];
        }
        if (vmax[u][i] > vmax[v][i]) {
            assignments.emplace_back(&vmax[v][i], vmax[v][i]);
            vmax[v][i] = vmax[u][i];
        }
    }
    rollback.push_back(assignments);
}


int main() {
    int n;
    cin>>n;
    for (int i = 1; i <= n; ++i) {
        int v[3];
        cin>>v[0]>>v[1]>>v[2];
        uf[i] = i;
        sz[i] = 1;
        vmin[i][0] = vmax[i][0] = v[0] - v[1] - v[2];
        vmin[i][1] = vmax[i][1] = v[0] - v[1] + v[2];
        vmin[i][2] = vmax[i][2] = v[0] + v[1] - v[2];
        vmin[i][3] = vmax[i][3] = v[0] + v[1] + v[2];
    }
    int q;
    cin>>q;
    while (q--) {
        int type;
        cin>>type;
        if (type == 1) {
            int u, v;
            cin>>u>>v;
            merge(u, v);
        } else if (type == 2) {
            for (const pair<int*, int> p : rollback.back())
                *p.first = p.second;
            rollback.pop_back();
        } else {
            int u, v;
            cin>>u>>v;
            cout<<query(u, v)<<endl;
        }
    }
}
