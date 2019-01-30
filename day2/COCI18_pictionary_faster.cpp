#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;
/////////////////////////////////////////////////////// BEGIN OF UNION-FIND WITH PARTIAL PERSISTENCE ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////// Note: this class supports both 0-indexed and 1-indexed elements ////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
class UnionFindPartial {
private:
    int m_current_time;
    std::vector<int> m_parent; // [0 .. size]
    std::vector<int> m_time;   // [0 .. size]
    std::vector<int> m_size;   // [0 .. size]
public:
    UnionFindPartial(const int size)
        : m_current_time(0)
        , m_parent(size+1)
        , m_time(size+1, 0)
        , m_size(size+1, 1)
    {
        for (int i = 0; i <= size; ++i)
            m_parent[i] = i;
    }
    inline int time() const {
        return m_current_time;
    }
    inline int find(int x, const int last_time) const {
        while (m_time[x] <= last_time && x != m_parent[x])
            x = m_parent[x];
        return x;
    }
    inline int find(const int x) const {
        return find(x, time());
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        m_current_time += 1;
        if (a != b) {
            if (m_size[a] < m_size[b]) {
                m_parent[a] = b;
                m_time[a] = m_current_time;
                m_size[b] += m_size[a];
            } else {
                m_parent[b] = a;
                m_time[b] = m_current_time;
                m_size[a] += m_size[b];
            }
        }
    }
    bool same(const int a, const int b) const {
        return find(a) == find(b);
    }
    bool same(const int a, const int b, const int last_time) const {
        return find(a, last_time) == find(b, last_time);
    }
    int find_time(int a, int b) const {
        int ans = 0;
        while (a != b) {
            if (m_parent[a] == a && m_parent[b] == b) return -1;
            if ((m_time[a] <= m_time[b] && m_parent[a] != a) || m_parent[b] == b) {
                ans = max(ans, m_time[a]);
                a = m_parent[a];
            } else {
                ans = max(ans, m_time[b]);
                b = m_parent[b];
            }
        }
        return ans;
    }
    int size(const int a) {
        const int gpa = find(a);
        return m_size[gpa];
    }
};
/////////////////////////////////////////////////////// END OF UNION-FIND WITH PARTIAL PERSISTENCY ///////////////////////////////////////////////////////
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin>>n>>m>>q;
    UnionFindPartial uf(n);
    map<int, int> ans;
    ans[uf.time()] = 0;
    for (int day = m; day >= 1; --day) {
        for (int i = 2; i*day <= n; ++i) {
            uf.merge(day, i*day);
            ans[uf.time()] = m-day+1;
        }
    }
    while (q--) {
        int a, b;
        cin>>a>>b;
        int time = uf.find_time(a, b);
        cout<<ans[time]<<'\n';
    }
}
