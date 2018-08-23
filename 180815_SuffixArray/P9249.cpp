#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Comparator {
    vector<int> g;
    int t;

    bool operator() (int a, int b) {
        if(g[a] != g[b]) return g[a] < g[b];
        return g[a+t] < g[b+t];
    }
};

char str[200005];
int offset, n;
int sa[200005];
int lcp[200005];

void getSuffixArray() {
    int t=1;
    vector<int> group(n+1);
    for(int i=0; i<n; i++)
        group[i] = str[i];
    group[n] = -1;

    for(int i=0; i<n; i++)
        sa[i] = i;

    vector<int> g(n+1);
    Comparator c;
    while(t < n) {
        c.g = group;
        c.t = t;
        sort(sa, sa+n, c);

        t*=2;
        if(t > n) break;

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
}

void getLongestCommonPrefixArray() {
    vector<int> pos(n);
    for(int i=0; i<n; i++)
        pos[sa[i]] = i;

    int k=0;

    for(int i=0; i<n; i++) {
        if(pos[i] == 0) continue;

        int t = sa[pos[i]-1];
        while(str[i+k] == str[t+k]) k++;
        lcp[pos[i]] = k;

        if(k) k--;
    }
}

int main() {
    scanf("%s", str);
    offset = strlen(str);
    str[offset] = '$';
    scanf("%s", str+offset+1);
    n = strlen(str);
    getSuffixArray();
    getLongestCommonPrefixArray();

    int max = 0;
    int maxIdx;
    for(int i=1; i<n; i++) {
        if( (sa[i] < offset && sa[i-1] > offset)
           || (sa[i] > offset && sa[i-1] < offset) ) {
            if(lcp[i] > max) {
                max = lcp[i];
                maxIdx = i;
            }
        }
    }

    printf("%d\n", max);
    str[sa[maxIdx] + max] = '\0';
    printf("%s", str+sa[maxIdx]);
    return 0;
}
