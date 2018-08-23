#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Comparator {
    vector<int> g;
    int t;

    Comparator(vector<int> _g, int _t): g(_g), t(_t) {}

    bool operator() (int a, int b) {
        if(g[a] != g[b]) return g[a] < g[b];
        return g[a+t] < g[b+t];
    }
};

vector<int> getSuffixArray(const string &str) {
    int n = str.size();

    int t=1;
    vector<int> group(n+1);
    for(int i=0; i<n; i++)
        group[i] = str[i];
    group[n] = -1;

    vector<int> sa(n);
    for(int i=0; i<n; i++)
        sa[i] = i;

    while(t < n) {
        Comparator c(group, t);
        sort(sa.begin(), sa.end(), c);

        t*=2;
        if(t > n) break;

        vector<int> g(n+1);
        g[n] = -1;
        g[sa[0]] = 0;
        for(int i=1; i<n; i++) {
            if(c(sa[i-1], sa[i]))
                g[sa[i]] = g[sa[i-1]] + 1;
            else
                g[sa[i]] = g[sa[i-1]];
        }
        group = g;
    }

    return sa;
}

vector<int> getLongestCommonPrefixArray(const string &str, const vector<int> &sa) {
    const char* c_str = str.c_str();
    int n = str.size();
    vector<int> pos(n);
    for(int i=0; i<n; i++)
        pos[sa[i]] = i;

    vector<int> lcp(n);

    int k=0;

    for(int i=0; i<n; i++) {
        if(pos[i] == 0) continue;

        int t = sa[pos[i]-1];
        while(c_str[i+k] == c_str[t+k]) k++;
        lcp[pos[i]] = k;

        if(k) k--;
    }

    return lcp;
}

int main() {
    string str1, str2;
    cin >> str1 >> str2;
    string str = str1 + '$' + str2;
    int offset = str1.size();
    vector<int> sa = getSuffixArray(str);
    vector<int> lcp = getLongestCommonPrefixArray(str, sa);

    int max = 0;
    int maxIdx;
    for(int i=1; i<sa.size(); i++) {
        if( (sa[i] >= offset && sa[i-1] >= offset)
           || (sa[i] < offset && sa[i-1] < offset)) continue;
        if(lcp[i] > max) {
            max = lcp[i];
            maxIdx = i;
        }
    }

    cout << max << endl;
    cout << str.substr(sa[maxIdx], max);
}
