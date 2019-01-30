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
    std::vector<int> m_uf; // [0 .. size]
    std::vector<int> m_sz; // [0 .. size]
public:
    UnionFind(const int size) {
        m_uf.reserve(size+1);
        m_sz.reserve(size+1);
        for (int i = 0; i <= size; ++i) {
            m_uf.push_back(i);
            m_sz.push_back(1);
        }
    }
    int find(const int x) {
        if (m_uf[x] != x)
            m_uf[x] = find(m_uf[x]);
        return m_uf[x];
    }
    void merge(const int a, const int b) {
        const int gpa = find(a);
        const int gpb = find(b);
        if (gpa != gpb) {
            if (m_sz[gpa] < m_sz[gpb]) {
                m_uf[gpa] = gpb;
                m_sz[gpb] += m_sz[gpa];
            } else {
                m_uf[gpb] = gpa;
                m_sz[gpa] += m_sz[gpb];
            }
        }
    }
    bool same(const int a, const int b) {
        return find(a) == find(b);
    }
    int size(const int a) {
        const int gpa = find(a);
        return m_sz[gpa];
    }
};
/////////////////////////////////////////////////////// END OF UNION-FIND ///////////////////////////////////////////////////////

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    auto get_friends = [&](int u) {
        return u;
    };
    auto get_enemies = [&](int u) {
        return n+u;
    };
    UnionFind uf(2*n);

    int c, x, y;
    while (cin>>c>>x>>y, c) {
        if (c == 1) {
            if (uf.same(get_friends(x), get_enemies(y))) {
                cout<<"-1"<<endl;
                continue;
            }
            uf.merge(get_friends(x), get_friends(y));
            uf.merge(get_enemies(x), get_enemies(y));
        } else if (c == 2) {
            if (uf.same(get_friends(x), get_friends(y))) {
                cout<<"-1"<<endl;
                continue;
            }
            uf.merge(get_friends(x), get_enemies(y));
            uf.merge(get_friends(y), get_enemies(x));
        } else if (c == 3) {
            bool ans = uf.same(get_friends(x), get_friends(y));
            cout<<(ans?'1':'0')<<endl;
        } else {
            bool ans = uf.same(get_friends(x), get_enemies(y));
            cout<<(ans?'1':'0')<<endl;
        }
    }
}
