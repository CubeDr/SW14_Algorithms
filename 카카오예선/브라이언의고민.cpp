#include <string>
#include <vector>

typedef std::pair<int, int> p;

using namespace std;

// 특수문자인지 여부 반환
bool isSpecial(char c) {
    return c>='a' && c<='z';
}

// 규칙 2가 적용되는 특수문자쌍의 위치
vector<p> rule2pos;

// 규칙 2가 적용되는 특수문자의 쌍을 찾아 rule2pos 에 넣어주는 함수
// 여기서 찾은 특수문자 쌍은 used[] 에 true 로 표기됨
bool buildRule2Pos(const string &sentence, bool used[]) {
    // 해당 특수문자를 검사했는지 여부를 저장하는 배열
    bool checked['z'-'a'+1] = {false,};
    // 해당 특수문자가 나온 횟수, 마지막으로 나온 위치
    int count, last;
    
    for(int i=0; i<sentence.size(); i++) {
        // 아직 확인하지 않은 특수문자에 대해서만 검사함
        if(!isSpecial(sentence[i]) || checked[sentence[i]-'a'])
            continue;
        // "이 문자 이제 확인합니다!"
        checked[sentence[i]-'a'] = true;
        // 현재까지 나온 횟수 : 1
        // 마지막으로 나온 위치 : 현재 위치
        count = 1;
        last = i;
        
        // 다음부터 검사하면서 해당 문자를 찾아서 개수와 위치 갱신
        for(int j=i+1; j<sentence.size(); j++) {
            if(sentence[i] == sentence[j]) {
                if(j == last+1) return false; // aa
                last = j;
                ++count;
            }
        }
        // 두개만 나왔으면 규칙2가 적용되는 특수문자 쌍!
        if(count == 2) {
            // 쌍의 위치를 저장하고 사용했다고 알림
            rule2pos.push_back({i, last});
            used[sentence[i]-'a'] = true;
        }
        // 검사한 곳까지 건너뜀
        i = last;
    }
    return true;
}

bool singleRule1(const string &sentence, int &idx, int end, string &answer, bool used[]) {
    answer += sentence[idx];
    idx++;

    bool specialTurn = true;
    char specialCharacter = 0;
    while(idx < end) {
        if(specialTurn) {
            if(!isSpecial(sentence[idx])) return true;
            else if(specialCharacter == 0) {
                specialCharacter = sentence[idx++];
                if(used[specialCharacter-'a']) return false;
                used[specialCharacter-'a'] = true;
            } else if(sentence[idx] != specialCharacter) return true;
            else idx++;
        } else {
            if(isSpecial(sentence[idx])) return false;
            answer += sentence[idx++];
        }

        specialTurn = !specialTurn;
    }
    return specialTurn;
}

bool multipleRule1(const string &sentence, int &idx, int end, string& answer, bool used[]) {
    while(idx < end) {
        if(isSpecial(sentence[idx]) || !singleRule1(sentence, idx, end, answer, used))
            return false;
        answer += " ";
    }
    return true;
}

bool rule2content(const string &sentence, int &idx, int end, string& answer, bool used[]) {
    bool containsSpecial = end>=idx+2 && isSpecial(sentence[idx+1]);
    bool specialTurn=false;
    bool special;
    char specialCharacter = 0;
    if(containsSpecial) {
        specialCharacter = sentence[idx+1];
        if(used[specialCharacter-'a']) return false;
        used[specialCharacter-'a'] = true;
    }

    for(; idx <= end; idx++) {
        special = isSpecial(sentence[idx]);
        if(containsSpecial && specialTurn) {
            if(!special || sentence[idx] != specialCharacter) return false;
        } else if(special) return false;

        if(!special) answer += sentence[idx];
        if(containsSpecial) specialTurn = !specialTurn;
    }
    answer += " ";
    return true;
}

string solution(string sentence) {
    bool used['z'-'a'+1] = {false,};
    rule2pos.clear();
    if(!buildRule2Pos(sentence, used)) return "invalid";

    string answer = "";
    int start = 0, end, t;
    for(int i=0; i<rule2pos.size(); i++) {
        end = rule2pos[i].first;
        if(start != end) {
            if(!multipleRule1(sentence, start, end, answer, used))
                return "invalid";
        }
        start = rule2pos[i].first + 1;
        end = rule2pos[i].second-1;
        if(!rule2content(sentence, start, end, answer, used))
            return "invalid";
        start = rule2pos[i].second+1;
    }
    end = sentence.size();
    if(start != end) {
        if(!multipleRule1(sentence, start, end, answer, used))
            return "invalid";
    }

    return answer.substr(0, answer.size()-1);
}