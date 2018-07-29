#include <iostream>
#include <string>
#include <vector>

typedef std::vector<int> v;

using namespace std;

/*        N = nk
 *    k   k   k   k   k
 * 같은 k 부분이 반복된다면
 * fail[N-1] = (n-1)*k
 * fail[N-1] = (n-1)*N/n
 *
 * fail[N-1] -> f
 * f = (n-1)*N/n
 * f*n = (n-1)*N
 * (N-f)*n = N
 * n = N / (N-f)
*/

int main() {
    string str;
    while(true) {
        cin >> str;
        if(str == ".") break;

        v fail(str.size(), 0);
        fill(fail.begin(), fail.end(), 0);
        for(int i=1, j=0; i<str.size(); i++) {
            while(j>0 && str[i] != str[j])
                j = fail[j-1];
            if(str[i] == str[j]) fail[i] = ++j;
        }

        int N = str.size();
        int f = fail[N-1];
        if(N % (N-f)) cout << 1 << endl;
        else cout << N/(N-f) << endl;
    }
    return 0;
}
