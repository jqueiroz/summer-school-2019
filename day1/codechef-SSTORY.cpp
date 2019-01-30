#include <bits/stdc++.h>
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;
/////////////////////////////////////////////////// BEGIN OF SPARSE TABLE ///////////////////////////////////////////////////
namespace {
    //TODO: implement sparse table without absorption (is it enough to have two query functions?)
    //TODO: support querying the position of the minimum value
    template<typename Data>
    class SparseTableAbsorption {
    private:
        const std::function<Data(Data, Data)> m_combine;
        std::vector<int> m_powers;
        std::vector<std::vector<Data>> m_table;
    public:
        SparseTableAbsorption(const std::vector<Data>& data, std::function<Data(Data, Data)> combine);

        Data query(const int i, const int j) const;
    };

    template<typename Data>
    SparseTableAbsorption<Data>::SparseTableAbsorption(const std::vector<Data>& data, const std::function<Data(Data, Data)> combine)
        : m_combine(combine)
    {
        const int n = (int) data.size();
        // Precompute powers
        m_powers.resize(n);
        m_powers[0] = 0;
        m_powers[1] = 0;
        for (int i = 2; i < n; ++i)
            m_powers[i] = m_powers[i>>1] + 1;
        // Build sparse table
        int levels = 0;
        while ((1<<levels) < n) ++levels;
        m_table.reserve(levels);
        m_table.push_back(data);
        for (int h = 1; h < levels; ++h) {
            const int pot = 1<<(h-1);
            m_table.push_back(m_table[h-1]);
            for (int i = 0; i < n-pot; ++i)
                m_table[h][i] = m_combine(m_table[h][i], m_table[h][i+pot]);
        }
    }

    template<typename Data>
    inline Data SparseTableAbsorption<Data>::query(const int i, const int j) const {
        assert(i <= j);
        const int size = j-i+1;
        const int pot = m_powers[size-1];
        return m_combine(m_table[pot][i], m_table[pot][j-(1<<pot)+1]);
        // combine([i, i+P-1], [j-P+1, j])
        // P <= j-i+1 => i+P-1 <= j (okay)
        // j-i+1 >= P => j-P+1 >= i (okay)
        // j-i+1 <= 2P => 2P >= j-i+1 => i+P-1 >= j-P (okay)
    }
}
/////////////////////////////////////////////////// END OF SPARSE TABLE ///////////////////////////////////////////////////
//////////////////////////////////////// BEGIN OF SUFFIX ARRAY ////////////////////////////////////////
namespace {
    class SuffixArrayLinearithmic {
    public:
        std::vector<int> rank; // rank[i] = k <=> s[k:] is the lexicographically ith suffix
        std::vector<int> pos;  // pos[k] = position of s[k:]
        std::vector<int> lcp;  // lcp[i] = lcp(lexicographically ith suffix, lexicographically (i+1)th suffix)
        SuffixArrayLinearithmic(const std::string& s)
            : rank(s.size())
            , pos(s.size())
            , lcp(s.size())
        {
            const int n = (int) s.size();
            if (n == 0)
                return;
            const int RADIX_EXP = 14;
            const int RADIX_FLAG = (1<<RADIX_EXP)-1;
            auto embed = [n](const long long x, const long long y) {
                return (x+1)*(n+1) + (y+1);
            };
            // Build compression table
            std::vector<int> table(256, 0);
            for (const char c : s)
                table[c] = 1;
            for (int i = 1; i < 256; ++i)
                table[i] += table[i-1];
            // Suffix array
            std::vector<long long> v(n);
            std::vector<int> bucket_begin(RADIX_FLAG+2);
            std::vector<int> sorted(n), sorted2(n);
            for (int i = 0; i < n; ++i)
                pos[i] = table[s[i]];
            for (int h = 1; h < n; h *= 2) {
                for (int i = 0; i < n; ++i)
                    v[i] = embed(pos[i], i+h < n ? pos[i+h] : -1);
                const long long maximum_value = *std::max_element(v.begin(), v.end());
                for (int i = 0; i < n; ++i)
                    sorted[i] = i;
                for (int val = 0; (maximum_value >> val) > 0; val += RADIX_EXP) {
                    std::fill(bucket_begin.begin(), bucket_begin.end(), 0);
                    for (int i = 0; i < n; ++i)
                        bucket_begin[((v[sorted[i]] >> val)&RADIX_FLAG)+1] += 1;
                    for (int i = 1; i <= RADIX_FLAG; ++i)
                        bucket_begin[i] += bucket_begin[i-1];
                    for (int i = 0; i < n; ++i)
                        sorted2[bucket_begin[(v[sorted[i]] >> val)&RADIX_FLAG]++] = sorted[i];
                    std::swap(sorted, sorted2);
                }
                int r = 0;
                for (int i = 0; i < n; ++i) {
                    if (i > 0 && v[sorted[i]] != v[sorted[i-1]]) ++r;
                    pos[sorted[i]] = r;
                }
                if (r == n-1) break; // important optimization!!!
            }
            // Rank
            for (int i = 0; i < n; ++i)
                rank[pos[i]] = i;
            // LCP
            lcp[n-1] = 0;
            for (int i = 0; i < n; ++i) {
                if (pos[i] != n-1) {
                    const int j = rank[pos[i]+1];
                    int& q = lcp[pos[i]] = 0;
                    if (i) q = std::max(q, lcp[pos[i-1]] - 1);
                    while (i+q < n && j+q < n && s[i+q] == s[j+q]) ++q;
                }
            }
        }

        int size() const {
            return (int) rank.size();
        }
    };

    // Source: https://github.com/dacin21/dacin21_codebook/blob/master/strings/suffix_array_faster.cpp
    class SuffixArrayLinear {
        unsigned char mask[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
        #define tget(i) ( (t[(i)/8]&mask[(i)%8]) ? 1 : 0 )
        #define tset(i, b) t[(i)/8]=(b) ? (unsigned char)(mask[(i)%8]|t[(i)/8]) : (unsigned char)((~mask[(i)%8])&t[(i)/8])
        #define chr(i) (cs==sizeof(int)?((int*)s)[i]:((unsigned char *)s)[i])
        #define isLMS(i) (i>0 && tget(i) && !tget(i-1))

        // find the start or end of each bucket
        void getBuckets(unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
            int i, sum = 0;
            for (i = 0; i <= K; i++)
                bkt[i] = 0;
            for (i = 0; i < n; i++)
                bkt[chr(i)]++;
            for (i = 0; i <= K; i++) {
                sum += bkt[i];
                bkt[i] = end ? sum : sum - bkt[i];
            }
        }
        void induceSAl(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
            int i, j;
            getBuckets(s, bkt, n, K, cs, end);
            for (i = 0; i < n; i++) {
                j = SA[i] - 1;
                if (j >= 0 && !tget(j))
                    SA[bkt[chr(j)]++] = j;
            }
        }
        void induceSAs(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
            int i, j;
            getBuckets(s, bkt, n, K, cs, end);
            for (i = n - 1; i >= 0; i--) {
                j = SA[i] - 1;
                if (j >= 0 && tget(j))
                    SA[--bkt[chr(j)]] = j;
            }
        }
        void SA_IS(unsigned char *s, int *SA, int n, int K, int cs) {
            int i, j;
            unsigned char *t = (unsigned char *) malloc(n / 8 + 1);
            tset(n-2, 0);
            tset(n-1, 1);
            for (i = n - 3; i >= 0; i--)
                tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);
            int *bkt = (int *) malloc(sizeof(int) * (K + 1));
            getBuckets(s, bkt, n, K, cs, true);
            for (i = 0; i < n; i++)
                SA[i] = -1;
            for (i = 1; i < n; i++)
                if (isLMS(i))
                    SA[--bkt[chr(i)]] = i;
            induceSAl(t, SA, s, bkt, n, K, cs, false);
            induceSAs(t, SA, s, bkt, n, K, cs, true);
            free(bkt);
            int n1 = 0;
            for (i = 0; i < n; i++)
                if (isLMS(SA[i]))
                    SA[n1++] = SA[i];
            for (i = n1; i < n; i++)
                SA[i] = -1;
            int name = 0, prev = -1;
            for (i = 0; i < n1; i++) {
                int pos = SA[i];
                bool diff = false;
                for (int d = 0; d < n; d++)
                    if (prev == -1 || chr(pos+d) != chr(prev+d) || tget(pos+d) != tget(prev+d)) {
                        diff = true;
                        break;
                    } else if (d > 0 && (isLMS(pos+d) || isLMS(prev+d)))
                        break;
                if (diff) {
                    name++;
                    prev = pos;
                }
                pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
                SA[n1 + pos] = name - 1;
            }
            for (i = n - 1, j = n - 1; i >= n1; i--)
                if (SA[i] >= 0)
                    SA[j--] = SA[i];
            int *SA1 = SA, *s1 = SA + n - n1;
            if (name < n1)
                SA_IS((unsigned char*) s1, SA1, n1, name - 1, sizeof(int));
            else
                for (i = 0; i < n1; i++)
                    SA1[s1[i]] = i;
            bkt = (int *) malloc(sizeof(int) * (K + 1));
            getBuckets(s, bkt, n, K, cs, true);
            for (i = 1, j = 0; i < n; i++)
                if (isLMS(i))
                    s1[j++] = i;
            for (i = 0; i < n1; i++)
                SA1[i] = s1[SA1[i]];
            for (i = n1; i < n; i++)
                SA[i] = -1;
            for (i = n1 - 1; i >= 0; i--) {
                j = SA[i];
                SA[i] = -1;
                SA[--bkt[chr(j)]] = j;
            }
            induceSAl(t, SA, s, bkt, n, K, cs, false);
            induceSAs(t, SA, s, bkt, n, K, cs, true);
            free(bkt);
            free(t);
        }
        public:
        std::vector<int> lcp, sa, inv;
        std::vector<int>& pos = inv;
        std::vector<int>& rank = sa;
        int N;
        private:

        void make_lcp(const char*s){
            lcp.resize(N);
            int k=0;
            for(int i=0;i<N;++i){
                if(inv[i]!=0){
                    for(int j = sa[inv[i]-1];s[i+k]==s[j+k];++k);
                    lcp[inv[i]-1]=k;
                    if(k)--k;
                }
            }
            lcp[N-1]=0;
        }
        public:
        SuffixArrayLinear(const string& s, const int max_sigma=256){
            N=(int)s.size();
            sa.resize(N);
            inv.resize(N);
            int *v = new int[N+3];
            SA_IS((unsigned char*)s.c_str(), v, N+1, max_sigma, 1);
            for(int i=0;i<N;++i){
                sa[i] = v[i+1];
                inv[sa[i]] = i;
            }
            make_lcp(s.c_str());
            delete[] v;
        }
        int size() const {
            return (int) rank.size();
        }
        #undef tget
        #undef tset
        #undef chr
        #undef isLMS
    };

    using SuffixArray = SuffixArrayLinear;

    long long count_distinct_substrings(const std::vector<int>& lcp) {
        const long long n = lcp.size();
        long long distinct_substrings = n*(n+1) / 2;
        for (int i = 0; i < n-1; ++i)
            distinct_substrings -= lcp[i];
        return distinct_substrings;
    }

    std::string concatenate_strings(const std::vector<std::string>& strings) {
        std::string ans;
        size_t total_size = 0;
        for (const std::string& str : strings)
            total_size += str.size();
        ans.reserve(total_size);
        for (const std::string& str : strings)
            ans += str;
        return ans;
    }

    class GeneralizedSuffixArray : public SuffixArray {
    private:
    public:
        const std::string str;
        const SparseTableAbsorption<int> lcp_st;
        GeneralizedSuffixArray(const std::string& str)
            : SuffixArray(str)
            , str(str)
            , lcp_st(lcp, [](const int x, const int y) { return std::min(x, y); })
        {
        }

        // Returns lcp(str[l1..], str[l2..])
        // Assumption: 0 <= l1, l2 < n
        // Running time: O(1)
        int compute_lcp(const int l1, const int l2) const {
            const int n = (int) str.size();
            if (l1 == l2)
                return n - l1;
            const int s1 = n - l1;
            const int s2 = n - l2;
            return std::min(s1, std::min(s2, pos[l1] < pos[l2] ? lcp_st.query(pos[l1], pos[l2]-1) : lcp_st.query(pos[l2], pos[l1]-1)));
        }

        // Returns lcp(str[l1..r1], str[l2..r2])
        // Assumption: 0 <= l1 <= r1 < n && 0 <= l2 <= r2 < n
        // Running time: O(1)
        int compute_lcp(const int l1, const int r1, const int l2, const int r2) const {
            const int s1 = r1 - l1 + 1;
            const int s2 = r2 - l2 + 1;
            if (l1 == l2)
                return std::min(s1, s2);
            return std::min(s1, std::min(s2, pos[l1] < pos[l2] ? lcp_st.query(pos[l1], pos[l2]-1) : lcp_st.query(pos[l2], pos[l1]-1)));
        }

        // Returns compare(str[l1..], str[l2..])
        // Assumption: 0 <= l1, l2 < n
        // Running time: O(1)
        int compare_strings(const int l1, const int l2) const {
            if (l1 == l2)
                return 0;
            const int n = (int) str.size();
            const int s1 = n - l1;
            const int s2 = n - l2;
            const int lcp = std::min(s1, std::min(s2, pos[l1] < pos[l2] ? lcp_st.query(pos[l1], pos[l2]-1) : lcp_st.query(pos[l2], pos[l1]-1)));
            if (lcp == s1 || lcp == s2) {
                if (s1 == s2)
                    return 0;
                else if (lcp == s1)
                    return -1;
                else
                    return +1;
            } else {
                return str[l1+lcp] < str[l2+lcp] ? -1 : +1;
            }
        }

        // Returns compare(str[l1..r1], str[l2..r2])
        // Assumption: 0 <= l1 <= r1 < n && 0 <= l2 <= r2 < n
        // Running time: O(1)
        int compare_strings(const int l1, const int r1, const int l2, const int r2) const {
            const int s1 = r1 - l1 + 1;
            const int s2 = r2 - l2 + 1;
            const int lcp = l1 == l2 ? std::min(s1, s2) : std::min(s1, std::min(s2, pos[l1] < pos[l2] ? lcp_st.query(pos[l1], pos[l2]-1) : lcp_st.query(pos[l2], pos[l1]-1)));
            if (lcp == s1 || lcp == s2) {
                if (s1 == s2)
                    return 0;
                else if (lcp == s1)
                    return -1;
                else
                    return +1;
            } else {
                return str[l1+lcp] < str[l2+lcp] ? -1 : +1;
            }
        }

        // Returns the largest interval [L, R] such that s[l..r] belongs to every substring of [L, R]
        // Running time: O(log n)
        std::pair<int, int> compute_range(const int l, const int r, const int hintl = 0, int hintr = -1) const {
            const int n = size();
            if (hintr == -1)
                hintr = n-1;
            const int len = r - l + 1;
            // Find the first suffix S[k..] such that S[k..] >= s[l..r]
            int bl = hintl, br = hintr;
            int ans1 = -1;
            while (bl <= br) {
                const int m = (bl+br) / 2;
                if (compare_strings(rank[m], n-1, l, r) >= 0) {
                    ans1 = m;
                    br = m-1;
                } else {
                    bl = m+1;
                }
            }
            assert(ans1 != -1);
            // Find the last suffix S[k..k+(r-l+1)] such that S[k..] == s[l..r]
            bl = ans1, br = hintr;
            int ans2 = -1;
            while (bl <= br) {
                const int m = (bl+br) / 2;
                if (rank[m]+len <= n && compare_strings(rank[m], rank[m]+len-1, l, r) == 0) {
                    ans2 = m;
                    bl = m+1;
                } else {
                    br = m-1;
                }
            }
            assert(ans2 != -1);
            return std::make_pair(ans1, ans2);
        }
    };

    // Note: empty strings are not allowed
    class MultiSuffixArray {
    public:
        std::vector<int> beg;
        GeneralizedSuffixArray gsa;
        MultiSuffixArray(const std::vector<std::string>& strings)
            : beg(strings.size()+1)
            , gsa(concatenate_strings(strings))
        {
            const int n = (int) strings.size();
            beg[0] = 0;
            for (int i = 1; i <= n; ++i)
                beg[i] = beg[i-1] + (int) strings[i-1].size();
        }

        // Returns lcp(strings[i], strings[j])
        // Running time: O(1)
        int compute_lcp(const int i, const int j) {
            return gsa.compute_lcp(beg[i], beg[i+1]-1, beg[j], beg[j+1]-1);
        }

        // Returns lcp(strings[i][il..], strings[j][jl..])
        // Running time: O(1)
        int compute_lcp(const int i, const int il, const int j, const int jl) {
            return gsa.compute_lcp(beg[i]+il, beg[i+1]-1, beg[j]+jl, beg[j+1]-1);
        }

        // Returns lcp(strings[i][il..ir], strings[j][jl..jr])
        // Running time: O(1)
        int compute_lcp(const int i, const int il, const int ir, const int j, const int jl, const int jr) {
            return gsa.compute_lcp(beg[i]+il, beg[i]+ir, beg[j]+jl, beg[j]+jr);
        }

        // Returns compare(strings[i], strings[j])
        // Running time: O(1)
        int compare_strings(const int i, const int j) const {
            return gsa.compare_strings(beg[i], beg[i+1]-1, beg[j], beg[j+1]-1);
        }

        // Returns compare(strings[i][il..], strings[j][jl..])
        // Running time: O(1)
        int compare_strings(const int i, const int il, const int j, const int jl) const {
            return gsa.compare_strings(beg[i]+il, beg[i+1]-1, beg[j]+jl, beg[j+1]-1);
        }

        // Returns compare(strings[i][il..ir], strings[j][jl..jr])
        // Running time: O(1)
        int compare_strings(const int i, const int il, const int ir, const int j, const int jl, const int jr) const {
            return gsa.compare_strings(beg[i]+il, beg[i]+ir, beg[j]+jl, beg[j]+jr);
        }
    };

    // Given a string T and several strings P[], answers queries of the following type: how many times does P[i][l..r] occurs inside T?
    // Note: empty strings are not allowed
    class SubstringCounting {
    public:
        const SuffixArray sa;
        const MultiSuffixArray msa;
        SubstringCounting(const std::string& text, const std::vector<std::string>& patterns)
            : sa(text)
            , msa([&]() {
                std::vector<std::string> all_strings;
                all_strings.push_back(text);
                for (const std::string& pattern : patterns)
                    all_strings.push_back(pattern);
                return all_strings;
            }())
        {
        }

        // Running time: O(1)
        int query(const int i, const int il, const int ir, const int hintl = 0, int hintr = -1) const {
            const int n = sa.size();
            if (hintr == -1)
                hintr = n-1;
            const int len = ir - il + 1;
            // Find the first suffix S[k..] such that S[k..] >= P[il..ir]
            int l = hintl, r = hintr;
            int ans1 = -1;
            while (l <= r) {
                const int m = (l+r) / 2;
                if (msa.compare_strings(0, sa.rank[m], n-1, 1+i, il, ir) >= 0) {
                    ans1 = m;
                    r = m-1;
                } else {
                    l = m+1;
                }
            }
            if (ans1 == -1)
                return 0;
            // Find the last suffix S[k..k+(r-l+1)] such that S[k..] == P[l..r]
            l = ans1, r = hintr;
            int ans2 = ans1-1;
            while (l <= r) {
                const int m = (l+r) / 2;
                if (sa.rank[m]+len <= n && msa.compare_strings(0, sa.rank[m], sa.rank[m]+len-1, 1+i, il, ir) == 0) {
                    ans2 = m;
                    l = m+1;
                } else {
                    r = m-1;
                }
            }
            return ans2-ans1+1;
        }
    };
}
//////////////////////////////////////// END OF SUFFIX ARRAY ////////////////////////////////////////

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    cin>>a>>b;
    const int as = (int) a.size();
    SuffixArrayLinear sa(a + "#" + b);
    int ans = 0;
    const int s = sa.size();
    for (int i = 1; i < s; ++i) {
        if (sa.rank[i-1] < as && sa.rank[i] > as) {
            ans = max(ans, sa.lcp[i-1]);
        } else if (sa.rank[i] < as && sa.rank[i-1] > as) {
            ans = max(ans, sa.lcp[i-1]);
        }
    }
    if (ans != 0) {
        int beg = 1e9;
        bool has_left = false;
        bool has_right = false;
        int min_right = 1e9;
        for (int i = 1; i < s; ++i) {
            if (sa.lcp[i-1] >= ans) {
                if (sa.rank[i-1] < as) {
                    has_left = true;
                } else if (sa.rank[i-1] > as) {
                    has_right = true;
                    min_right = min(min_right, sa.rank[i-1]);
                }
                if (sa.rank[i] < as) {
                    has_left = true;
                } else if (sa.rank[i] > as) {
                    has_right = true;
                    min_right = min(min_right, sa.rank[i]);
                }
            } else {
                has_left = false;
                has_right = false;
                min_right = 1e9;
            }
            if (has_left && has_right)
                beg = min(beg, min_right);
        }
        cout<<b.substr(beg-as-1, ans)<<endl;
    }
    cout<<ans<<endl;
}
