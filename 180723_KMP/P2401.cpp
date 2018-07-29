#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct KMP {
private:
    std::string _pattern;
    std::vector<int> fail;
public:
    KMP(std::string pattern): _pattern(pattern) {
        fail.resize(pattern.size());
        std::fill(fail.begin(), fail.end(), 0);
        for(int i=1, j=0; i<pattern.size(); i++) {
            while(j>0 && pattern[i] != pattern[j])
                j = fail[j-1];
            if(pattern[i] == pattern[j]) fail[i] = ++j;
        }
    }

    std::vector<int> search(std::string content) {
        std::vector<int> result;
        for(int i=0, j=0; i<content.size(); i++) {
            while(j>0 && content[i] != _pattern[j])
                j = fail[j-1];
            if(content[i] == _pattern[j]) {
                if(j == _pattern.size()-1) {
                    result.push_back(i - _pattern.size() + 1);
                    j = fail[j];
                } else j++;
            }
        }
        return result;
    }
};

using namespace std;

string content;
vector<int> matchLength[100000];

int mem[100000];
int maxLength(int offset = 0) {
    if(offset >= content.size()) return 0;
    if(mem[offset] != -1) return mem[offset];

    // 현재 위치를 비우는 경우
    int max = maxLength(offset+1);

    // 현재 위치에서 단어를 사용하는 경우
    int w, t;
    for(int i=0; i<matchLength[offset].size(); i++) {
        w = matchLength[offset][i];
        t = w + maxLength(offset+w);
        if(t > max) max = t;
    }

    return mem[offset] = max;
}

int main() {
    cin >> content;

    int N;
    cin >> N;
    string str;

    for(int i=0; i<N; i++) {
        cin >> str;
        vector<int> pos = KMP(str).search(content);
        for(int j=0; j<pos.size(); j++)
            matchLength[pos[j]].push_back(str.size());
    }

    fill(mem, mem + content.size(), -1);
    cout << maxLength();
    return 0;
}
