#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    unordered_map<string, int> um;
    string answer;

    for(int i=0; i<completion.size(); i++){
        um[completion[i]] += 1; //*****동명이인이 있을 수 있음
        // um.insert(make_pair(completion[i], 1));
    }

    for(int i=0; i<participant.size(); i++){
        if(um.find(participant[i]) == um.end() || um[participant[i]] == 0){
            answer = participant[i];
            break;
        }else{
            um[participant[i]] -= 1;
        }
    }

    return answer;
}