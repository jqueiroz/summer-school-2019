#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;
/////////////////////////////////////////////////////// BEGIN OF BIT-2D ///////////////////////////////////////////////////////
template<typename Data, typename Folder, typename InverseFn>
class Bit2D {
private:
    const int size, first_index, last_index, delta_index;
    std::vector<std::vector<Data>> v;
public:
    const Folder folder;
    const InverseFn inverse_fn;
    Bit2D(const int _first_index, const int _last_index)
        : size(_last_index - _first_index + 1)
        , first_index(_first_index)
        , last_index(_last_index)
        , delta_index(1 - _first_index)
        , v(size+1, vector<Data>(size+1))
        , folder{}
        , inverse_fn{}
    {
    }
    // Normal: returns sum of v[1..i][1..j]
    // Inverted: returns v[i][j]
    Data get(int i, int j) const {
        i += delta_index;
        j += delta_index;
        Data acc = Data();
        for (int ii = i; ii > 0; ii -= ii&-ii)
        for (int jj = j; jj > 0; jj -= jj&-jj)
            acc = folder(acc, v[ii][jj]);
        return acc;
    }
    // Normal: increases v[i][j]
    // Inverted: increases v[i..size][j..size]
    void add(int i, int j, const Data val) {
        i += delta_index;
        j += delta_index;
        for (int ii = i; ii <= size; ii += ii&-ii)
        for (int jj = j; jj <= size; jj += jj&-jj)
            v[ii][jj] = folder(v[ii][jj], val);
    }
    // Normal: returns sum of v[i1..i2][j1..j2]
    Data get_rect(const int i1, const int j1, const int i2, const int j2) const {
        Data ret = get(i2, j2);
        if (i1 > first_index)
            ret = folder(ret, inverse_fn(get(i1-1, j2)));
        if (j1 > first_index)
            ret = folder(ret, inverse_fn(get(i2, j1-1)));
        if (i1 > first_index && j1 > first_index)
            ret = folder(ret, get(i1-1, j1-1));
        return ret;
    }
    // Inverted: increases v[i1..i2][j1..j2]
    void add_rect(const int i1, const int j1, const int i2, const int j2, const Data val) {
        const Data inv = inverse_fn(val);
        add(i1, j1, val);
        if (i2 < last_index)
            add(i2+1, j1, inv);
        if (j2 < last_index)
            add(i1, j2+1, inv);
        if (i2 < last_index && j2 < last_index)
            add(i2+1, j2+1, val);
    }
    // Normal: returns v[i][j]
    inline Data get_element(const int i, const int j) const {
        return get_rect(i, j, i, j);
    }
    // Normal: sets v[i][j]
    inline void set_element(const int i, const int j, const Data val) {
        const Data old = get_element(i, j);
        const Data delta = folder(val, inverse_fn(old));
        add(i, j, delta);
    }
};
template<typename T>
struct Identity {
    T operator()(const T x) const { return x; }
};
template<typename T>
using SumBit2D = Bit2D<T, std::plus<T>, std::negate<T>>;
template<typename T>
using XorBit2D = Bit2D<T, std::bit_xor<T>, Identity<T>>;
/////////////////////////////////////////////////////// END OF BIT-2D ///////////////////////////////////////////////////////
struct Rectangle {
    int x1, y1, x2, y2;

    uint64_t get_hash() {
        uint64_t x1 = this->x1;
        uint64_t y1 = this->y1;
        uint64_t x2 = this->x2;
        uint64_t y2 = this->y2;

        return x1 + y1*28934751 + x2*843728912 + y2*478123981;
    }
};

Rectangle read_rectangle() {
    Rectangle r;
    cin>>r.x1>>r.y1>>r.x2>>r.y2;
    return r;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    XorBit2D<uint64_t> bit(1, 5000);
    int queries;
    cin>>queries;
    vector<Rectangle> history(queries+1);
    for (int query = 1; query <= queries; ++query) {
        int type;
        cin>>type;
        if (type == 1) {
            history[query] = read_rectangle();
            Rectangle r = history[query];
            //cerr<<"adding hash ("<<r.x1<<", "<<r.y1<<", "<<r.x2<<", "<<r.y2<<"): "<<r.get_hash()<<endl;
            bit.add_rect(r.x1, r.y1, r.x2, r.y2, r.get_hash());
        } else if (type == 2) {
            int id;
            cin>>id;
            Rectangle r = history[id];
            bit.add_rect(r.x1, r.y1, r.x2, r.y2, r.get_hash());
            //cerr<<"removing hash: "<<r.get_hash()<<endl;
        } else {
            int x1, y1, x2, y2;
            cin>>x1>>y1>>x2>>y2;
            const uint64_t h1 = bit.get(x1, y1);
            const uint64_t h2 = bit.get(x2, y2);
            //cerr<<"querying hash ("<<x1<<", "<<y1<<"): "<<h1<<endl;
            //cerr<<"querying hash ("<<x2<<", "<<y2<<"): "<<h2<<endl;
            cout<<(h1 == h2 ? 'Y' : 'N');
            //cerr<<endl;
        }
    }
    cout<<endl;
}
