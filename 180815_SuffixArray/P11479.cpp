#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ���̻���� ���ڿ� ������� �����ϱ� ���� ����
struct Comparator {
    // t������ ������ �� �� ���̻簡 ���� �׷�
    const vector<int> &group;
    int t;

    Comparator(const vector<int> &_g, int _t): group(_g), t(_t) {}

    bool operator() (int a, int b) {
        // �̹� �񱳸� �ߴ� ���̻���̸� ������ ���� ��� ��ȯ
        if(group[a] != group[b]) return group[a] < group[b];
        // �� t ���� �Ȱ����� �� ���� t�� ���ڷ� ��
        // �̰� �ٸ��� �ٸ� �׷����� �з��ǰ� ������ ���� �׷����� �з���
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
    // s[i:] �� ���ĵ� ��ġ
    vector<int> pos(sa.size());
    for(int i=0; i<sa.size(); i++)
        pos[sa[i]] = i;

    vector<int> lcp(sa.size());


    // ��ġ�ϴ� ����
    int k=0;

    // ���� ª�� ���̻���� ����
    for(int i=0; i<sa.size(); i++) {
        // ���� ���� ���̻簡 ������ ���
        if(pos[i] == 0) continue;

        // �ٷ� �� ���̻�
        int j = sa[pos[i]-1];
        while(s[i+k] == s[j+k]) k++;
        lcp[pos[i]] = k;

        // �տ� �� ���ڸ� �����ϹǷ� ���� �κ� ���� 1 ����
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
