#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

// Running time: O(sqrt(n))
template<typename T>
void find_divisors(const T n, vector<T>& ret) {
    const int s = (int) sqrt(n);
    for (int i = 1; i < s; ++i) {
        if (n % i == 0) {
            ret.push_back(i);
            ret.push_back(n / i);
        }
    }
    if (n % s == 0) {
        ret.push_back(s);
        if (s != n / s)
            ret.push_back(n / s);
    }
}

// Running time: O(sqrt(n))
template<typename T>
inline const vector<T>& find_divisors(const T n) {
    static vector<T> ret;
    ret.clear();
    find_divisors(n, ret);
    return ret;
}

map<ll, ll> dp;
ll solve(ll q) {
    if (dp.count(q))
        return dp[q];
    int moves = 0;
    for (ll d : find_divisors(q)) {
        if (d != 1 && d != q) {
            moves += 1;
            if (solve(d) == -1)
                return dp[q] = d;
        }
    }
    if (moves)
        return dp[q] = -1;
    else
        return dp[q] = 0;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll q;
    cin>>q;
    ll x = solve(q);
    if (x == -1)
        cout<<2<<endl;
    else
        cout<<1<<endl<<x<<endl;
}
