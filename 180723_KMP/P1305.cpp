#include <iostream>
#include <vector>
#include <string>

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

    std::vector<int> getFailArray() {
        return std::vector<int>(fail.begin(), fail.end());
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

int main() {
    int n;
    string str;

    cin >> n >> str;
    KMP kmp(str);
    vector<int> f = kmp.getFailArray();
    cout << n - f[f.size()-1];
    return 0;
}
