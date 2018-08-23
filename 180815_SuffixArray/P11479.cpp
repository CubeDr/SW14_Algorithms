#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 접미사들을 문자열 순서대로 정렬하기 위한 비교자
struct Comparator {
    // t개까지 비교했을 때 각 접미사가 속한 그룹
    const vector<int> &group;
    int t;

    Comparator(const vector<int> &_g, int _t): group(_g), t(_t) {}

    bool operator() (int a, int b) {
        // 이미 비교를 했던 접미사들이면 이전에 비교한 결과 반환
        if(group[a] != group[b]) return group[a] < group[b];
        // 앞 t 개가 똑같으면 그 다음 t개 문자로 비교
        // 이게 다르면 다른 그룹으로 분류되고 같으면 같은 그룹으로 분류됨
        return group[a+t] < group[b+t];
    }
};

vector<int> getSuffixArray(const string &s) {
    int n = s.size();

    int t = 1;
    vector<int> group(n+1);
    for(int i=0; i<n; i++) group[i] = s[i];
    group[n] = -1;

    vector<int> perm(n);
    for(int i=0; i<n; i++) perm[i] = i;

    while(t<n) {
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        t *= 2;
        if(t >= n) break;

        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i=1; i<n; i++) {
            if(compareUsing2T(perm[i-1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            else
                newGroup[perm[i]] = newGroup[perm[i-1]];
        }
        group = newGroup;
    }
    return perm;
}

vector<int> getLongestCommonPrefixArray(const string &s, const vector<int> &sa) {
    // s[i:] 의 정렬된 위치
    vector<int> pos(sa.size());
    for(int i=0; i<sa.size(); i++)
        pos[sa[i]] = i;

    vector<int> lcp(sa.size());


    // 일치하는 개수
    int k=0;

    // 가장 짧은 접미사부터 시작
    for(int i=0; i<sa.size(); i++) {
        // 비교할 이전 접미사가 없으면 통과
        if(pos[i] == 0) continue;

        // 바로 위 접미사
        int j = sa[pos[i]-1];
        while(s[i+k] == s[j+k]) k++;
        lcp[pos[i]] = k;

        // 앞에 한 문자를 제거하므로 공통 부분 길이 1 감소
        if(k) k--;
    }

    return lcp;
}

int main() {
    string str;
    cin >> str;
    vector<int> lcp = getLongestCommonPrefixArray(str, getSuffixArray(str));
    int n = str.size();
    int duplicates = 0;
    for(int i=0; i<lcp.size(); i++)
        duplicates += lcp[i];
    cout << (n*(n+1)/2) - duplicates;
    return 0;
}
