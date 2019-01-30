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
void solve() {
    int n, k;
    cin>>n>>k;
    UnionFind uf(3*n);
    auto get_same = [&](const int u) {
        return u-1;
    };
    auto get_above = [&](const int u) {
        return n+u-1;
    };
    auto get_below = [&](const int u) {
        return 2*n+u-1;
    };
    int total_lies = 0;
    while (k--) {
        int d, x, y;
        cin>>d>>x>>y;
        if (x > n || y > n) {
            total_lies += 1;
        } else if (d == 1) {
            if (uf.same(get_same(x), get_above(y))) {
                total_lies += 1;
            } else if (uf.same(get_same(x), get_below(y))) {
                total_lies += 1;
            } else {
                uf.merge(get_same(x), get_same(y));
                uf.merge(get_above(x), get_above(y));
                uf.merge(get_below(x), get_below(y));
            }
        } else {
            if (x == y) {
                total_lies += 1;
            } else if (uf.same(get_same(x), get_same(y))) {
                total_lies += 1;
            } else if (uf.same(get_same(x), get_below(y))) {
                total_lies += 1;
            } else if (uf.same(get_below(x), get_above(y))) {
                total_lies += 1;
            } else {
                uf.merge(get_same(x), get_above(y));
                uf.merge(get_same(y), get_below(x));
                uf.merge(get_above(x), get_below(y));
            }
        }
    }
    cout<<total_lies<<'\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int testcases;
    cin>>testcases;
    while (testcases--) {
        solve();
    }
}
