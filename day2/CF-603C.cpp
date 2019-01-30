#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int solve_even(const int x) {
    if (x == 0)
        return 0;
    else if (x == 1)
        return 1;
    else if (x == 2)
        return 2;
    else
        return 1 - (x%2);
}

int solve_odd(const int x) {
    if (x == 0)
        return 0;
    else if (x == 1)
        return 1;
    else if (x == 2)
        return 0;
    else if (x == 3)
        return 1;
    else if (x == 4)
        return 2;
    else if (x % 2)
        return 0;
    const int nimber = solve_odd(x / 2);
    if (nimber == 1)
        return 2;
    else
        return 1;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin>>n>>k;
    int nimber = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin>>x;
        if (k % 2)
            nimber ^= solve_odd(x);
        else
            nimber ^= solve_even(x);
    }
    cout<<(nimber ? "Kevin" : "Nicky")<<endl;
}
