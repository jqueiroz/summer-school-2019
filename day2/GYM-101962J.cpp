#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;
/////////////////////////////////////////////////////// BEGIN OF SPARSE UNION-FIND ///////////////////////////////////////////////////////
// Note: this class supports arbitrarily indexed elements
class SparseUnionFind {
private:
    std::vector<std::pair<int, int>> m_edges;
    std::map<int, int> m_parent;
    std::map<int, int> m_size;
public:
    // Complexity: O(log(n) alpha(n))
    int find(const int x) {
        auto it = m_parent.find(x);
        if (it == m_parent.end())
            return x;
        return it->second = find(it->second);
    }
    // Complexity: O(log(n) alpha(n))
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (size(a) > size(b))
            swap(a, b);
        if (a != b) {
            m_edges.push_back({a, b});
            m_parent[a] = b;
            m_size[b] += m_size[a];
        }
    }
    // Complexity: O(log(n) alpha(n))
    bool same(const int a, const int b) {
        return find(a) == find(b);
    }
    // Complexity: O(log(n) alpha(n))
    int size(const int a) {
        auto it = m_size.find(a);
        if (it == m_size.end())
            return 1;
        else
            return it->second;
    }
    // Complexity: O(1)
    const std::vector<std::pair<int, int>>& edges() const {
        return m_edges;
    }
    // Complexity: O(1)
    const int edges_count() const {
        return (int) m_edges.size();
    }
    // Note: this method may invalidate the rhs
    // Complexity: O(k log(n) alpha(n)) where k = min(lhs_size, rhs_size) and n = (lhs_size + rhs_size)
    void merge_with(SparseUnionFind&& rhs) {
        if (m_edges.size() < rhs.m_edges.size()) {
            std::swap(m_parent, rhs.m_parent);
            std::swap(m_size, rhs.m_size);
            std::swap(m_edges, rhs.m_edges);
        }
        for (auto e : rhs.m_edges)
            merge(e.first, e.second);
    }
};
/////////////////////////////////////////////////////// END OF UNION-FIND ///////////////////////////////////////////////////////

const int MAX_N = 100000;
vector<int> children[MAX_N+1];
pair<int, int> street[MAX_N+1];
int answers[MAX_N+1];
int n, k;

SparseUnionFind solve(const int v) {
    SparseUnionFind master;
    if (street[v].first != 0)
        master.merge(street[v].first, street[v].second);
    for (const int w : children[v])
        master.merge_with(solve(w));
    answers[v] = k - master.edges_count();
    return master;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>k;
    for (int i = 2; i <= n; ++i) {
        int boss;
        cin>>boss;
        children[boss].push_back(i);
    }
    for (int i = 1; i <= n; ++i)
        cin>>street[i].first>>street[i].second;
    solve(1);
    for (int i = 1; i <= n; ++i)
        cout<<answers[i]<<'\n';
}
