#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;
/////////////////////////////////////////////////////// BEGIN OF UNION-FIND ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////// Note: this class supports both 0-indexed and 1-indexed elements ////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
class UnionFind {
private:
    std::vector<int> m_parent; // [0 .. size]
    std::vector<int> m_size;   // [0 .. size]
public:
    UnionFind(const int size) {
        m_parent.reserve(size+1);
        m_size.reserve(size+1);
        for (int i = 0; i <= size; ++i) {
            m_parent.push_back(i);
            m_size.push_back(1);
        }
    }
    int find(const int x) {
        if (m_parent[x] != x)
            m_parent[x] = find(m_parent[x]);
        return m_parent[x];
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (m_size[a] > m_size[b])
            swap(a, b);
        if (a != b) {
            m_parent[a] = b;
            m_size[b] += m_size[a];
        }
    }
    bool same(const int a, const int b) {
        return find(a) == find(b);
    }
    int size(const int a) {
        return m_size[find(a)];
    }
};
/////////////////////////////////////////////////////// END OF UNION-FIND ///////////////////////////////////////////////////////

struct Road {
    int u, v, c;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin>>n>>m>>k;
    vector<Road> roads(m);
    for (int i = 0; i < m; ++i)
        cin>>roads[i].u>>roads[i].v>>roads[i].c;
    UnionFind uf1(n), uf2(n);
    for (auto r : roads)
        if (r.c == 1)
            uf1.merge(r.u, r.v);
    vector<Road> ans;
    int cnt_cobblestone = 0;
    for (auto r : roads)
        if (!uf1.same(r.u, r.v))
            if (r.c == 0 && cnt_cobblestone < k)
                if (!uf2.same(r.u, r.v))
                    ans.push_back(r),
                    uf2.merge(r.u, r.v),
                    cnt_cobblestone += 1;
    for (auto r : roads)
        if (r.c == 0 && cnt_cobblestone < k)
            if (!uf2.same(r.u, r.v))
                ans.push_back(r),
                uf2.merge(r.u, r.v),
                cnt_cobblestone += 1;
    if (cnt_cobblestone != k) {
        cout<<"no solution\n";
        return 0;
    }
    for (auto r : roads)
        if (r.c == 1)
            if (!uf2.same(r.u, r.v))
                ans.push_back(r),
                uf2.merge(r.u, r.v);
    for (auto r : ans)
        cout<<r.u<<' '<<r.v<<' '<<r.c<<'\n';
}
