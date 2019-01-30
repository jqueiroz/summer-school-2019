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

    int n, m, q;
    cin>>n>>m>>q;
    map<string, int> wid;
    for (int i = 0; i < n; ++i) {
        string x;
        cin>>x;
        wid[x] = i;
    }
    UnionFind uf(2*n);
    auto get_synonyms = [&](const string& u) {
        return wid[u];
    };
    auto get_antonyms = [&](const string& u) {
        return n+wid[u];
    };
    while (m--) {
        int type;
        string x, y;
        cin>>type>>x>>y;
        if (type == 1) {
            if (uf.same(get_synonyms(x), get_antonyms(y))) {
                cout<<"NO\n";
            } else {
                uf.merge(get_synonyms(x), get_synonyms(y));
                uf.merge(get_antonyms(x), get_antonyms(y));
                cout<<"YES\n";
            }
        } else {
            if (uf.same(get_synonyms(x), get_synonyms(y))) {
                cout<<"NO\n";
            } else {
                uf.merge(get_synonyms(x), get_antonyms(y));
                uf.merge(get_antonyms(x), get_synonyms(y));
                cout<<"YES\n";
            }
        }
    }
    while (q--) {
        string x, y;
        cin>>x>>y;
        if (uf.same(get_synonyms(x), get_synonyms(y))) {
            cout<<"1\n";
        } else if (uf.same(get_synonyms(x), get_antonyms(y))) {
            cout<<"2\n";
        } else {
            cout<<"3\n";
        }
    }
}
