#include <string>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool comp(const string &a, const string& b){
    return a+b > b+a;
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> v;
    for(int i=0; i<numbers.size(); i++){
        v.push_back(to_string(numbers[i])); //to_string() 통해 문자열 변환
    }
    sort(v.begin(), v.end(), comp);
    for(int i=0; i<v.size(); i++){
        if(v[0] == "0"){
            answer = "0";
            break;
        }
        answer += v[i];
    }
    return answer;
}