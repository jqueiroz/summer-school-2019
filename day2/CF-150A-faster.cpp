#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll q;
    cin>>q;
    ll original = q;
    ll s = (int) sqrt(q);
    ll ans = 1;
    int remaining = 2;
    for (ll i = 2; i <= s; ++i) {
        if (remaining == 0) break;
        if (q % i == 0) {
            while (q % i == 0) {
                if (remaining == 0) break;
                q /= i;
                ans *= i;
                remaining -= 1;
            }
        }
    }
    if (remaining == 2) {
        cout<<"1"<<endl<<"0"<<endl;
        return 0;
    }
    if (q >= 2 && remaining != 0) {
        ans *= q;
        remaining -= 1;
    }
    if (ans == original || remaining != 0) {
        cout<<"2"<<endl;
    } else {
        cout<<"1"<<endl<<ans<<endl;
    }
}
