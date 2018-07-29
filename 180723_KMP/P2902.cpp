#include <iostream>
#include <string>

using namespace std;

int main() {
    string l;
    cin >> l;
    cout << l[0];
    for(int i=1; i<l.size(); i++)
        if(l[i] == '-') cout << l[++i];
    return 0;
}
