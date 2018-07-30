#include <cstdio>
#include <vector>
#include <string>

class KMP {
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

int gcd(int a, int b) {
    if(a==0) return b;
    return gcd(b%a, a);
}

int main() {
    char str1[1000001];
    char str2[1000001];

    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++)
        scanf(" %c", &str1[i]);
    str1[n] = '\0';
    for(int i=0; i<n; i++)
        scanf(" %c", &str2[i]);
    str2[n] = '\0';

    KMP kmp(str2);
    string content(str1);
    content += content;
    content = content.substr(0, content.size()-1);
    int count = kmp.search(content).size();
    int g = gcd(count, n);
    printf("%d/%d", count/g, n/g);

    return 0;
}
