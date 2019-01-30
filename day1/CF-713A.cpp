#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;

vector<bool> get_pattern(string x) {
    reverse(x.begin(), x.end());
    while (x.size() <= 20)
        x.push_back(0);
    reverse(x.begin(), x.end());
    vector<bool> pattern;
    for (char c : x) {
        int digit = c - '0';
        pattern.push_back(digit % 2);
    }
    return pattern;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;
    map<vector<bool>, int> cnt;
    while (t--) {
        string type;
        string value;
        cin>>type>>value;
        vector<bool> pattern = get_pattern(value);
        if (type == "+") {
            cnt[pattern] += 1;
        } else if (type == "-") {
            cnt[pattern] -= 1;
        } else {
            cout<<cnt[pattern]<<"\n";
        }
    }
}
