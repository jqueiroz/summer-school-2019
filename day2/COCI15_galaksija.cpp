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
        if (m_size[a] > m_size[b]) {
            /* In this particular problem, we assume that "merge" is only
             * called when "a" is already known to be the smaller set.
             * */
            throw 42;
            swap(a, b);
        }
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

struct Edge {
    int a, b, z;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read input
    int n;
    cin>>n;
    vector<Edge> unordered_edges;
    for (int i = 0; i < n-1; ++i) {
        int a, b, z;
        cin>>a>>b>>z;
        unordered_edges.push_back({a-1, b-1, z});
    }
    // Sort edges
    vector<Edge> edges;
    for (int i = 0; i < n-1; ++i) {
        int id;
        cin>>id;
        edges.push_back(unordered_edges[id-1]);
    }
    reverse(edges.begin(), edges.end());
    // Compute answers
    vector<long long> answers = {0};
    vector<pair<int, int>> graph[n];
    UnionFind uf(n);
    long long ans = 0;
    map<int, int> vert_xor;   // vert_xor[v]: path-aggregate xor from the leader (root) of v to v
    map<int, int> cnt_xor[n]; // cnt_xor[v][x]: the number of paths starting at the leader (root) of v with aggregate xor value equal to "x"
    for (int i = 0; i < n; ++i) {
        vert_xor[i] = 0;
        cnt_xor[i][0] = 1;
    }
    for (Edge e : edges) {
        int a = uf.find(e.a);
        int b = uf.find(e.b);
        int z = e.z;
        assert(a != b);
        if (uf.size(a) > uf.size(b)) {
            swap(e.a, e.b);
            swap(a, b);
        }

        const int xor_root = vert_xor[e.b];
        function<void(int,int,int)> dfs1 = [&](const int u, const int v, const int val) {
            ans += cnt_xor[b][val ^ z ^ xor_root];
            for (const pair<int, int> e : graph[v])
                if (e.first != u)
                    dfs1(v, e.first, e.second ^ val);
        };
        function<void(int,int,int)> dfs2 = [&](const int u, const int v, const int val) {
            vert_xor[v] = val ^ z ^ xor_root;
            cnt_xor[b][vert_xor[v]] += 1;
            for (const pair<int, int> e : graph[v])
                if (e.first != u)
                    dfs2(v, e.first, e.second ^ val);
        };
        dfs1(-1, e.a, 0);
        dfs2(-1, e.a, 0);

        graph[e.a].push_back({e.b, z});
        graph[e.b].push_back({e.a, z});
        uf.merge(a, b);
        answers.push_back(ans);
        //printf("ans = %lld\n", ans);
    }
    // Print answers
    reverse(answers.begin(), answers.end());
    for (long long x : answers)
        cout<<x<<'\n';
}
