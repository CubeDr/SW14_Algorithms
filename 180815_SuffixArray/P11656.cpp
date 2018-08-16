#include <iostream>
#include <vector>
#include <string>
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

vector<int> getSuffixArray(const string& s) {
    int n = s.size();

	// 현재까지 비교한 문자의 개수 
    int t = 1;
	// 각 접미사가 속한 그룹 번호
	// 처음엔 각 문자를 이용해 정렬된 그룹번호를 바로 부여할 수 있음
    vector<int> group(n+1);
    for(int i=0; i<n; i++) group[i] = s[i];
	// Comparator 에서 비교할 때 +t 가 문자열의 끝이면 앞으로 정렬될 수 있게 -1을 넣어줌
    group[n] = -1;

	// 접미사 배열
	// 정렬된 접미사의 시작 위치가 들어있음
    vector<int> perm(n);
    for(int i=0; i<n; i++) perm[i] = i;

    while(t<n) {
		// 나눠놓은 그룹 번호를 이용해 접미사들을 정렬함
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        t *= 2;
        if(t >= n) break;

		// 정렬된 접미사들의 첫번째부터 다시 그룹 번호를 부여 
		// perm[] 이 정렬된 상태이므로 perm[] 순서대로 번호 부여
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

int main() {
    string str;
    cin >> str;
    vector<int> suffixArray = getSuffixArray(str);
    for(int i=0; i<suffixArray.size(); i++)
        cout << str.substr(suffixArray[i]) << endl;
    return 0;
}
