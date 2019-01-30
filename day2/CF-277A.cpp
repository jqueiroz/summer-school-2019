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

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    UnionFind uf(n+m);
    auto get_lang = [&](int u) {
        assert(1 <= u && u <= m);
        return u-1;
    };
    auto get_emp = [&](int u) {
        assert(1 <= u && u <= n);
        return m+u-1;
    };
    int total_langs_known = 0;
    for (int i = 1; i <= n; ++i) {
        int k;
        cin>>k;
        total_langs_known += k;
        while (k--) {
            int lang;
            cin>>lang;
            uf.merge(get_emp(i), get_lang(lang));
        }
    }

    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        if (!uf.same(get_emp(1), get_emp(i))) {
            uf.merge(get_emp(1), get_emp(i));
            ans += 1;
        }
    }
    if (total_langs_known == 0)
        ans = n;
    cout<<ans<<endl;
}
