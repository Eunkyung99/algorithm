#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    unordered_map <string, int> um;
    
    for(int i=0; i<clothes.size(); i++){
        string types = clothes[i][1];
        um[types]+=1;
    }
    
    for(auto i: um){ //******** unordered_map 순회방법 i는 pair임
        answer *= (i.second + 1);  //각 종류별 개수 + 1을 곱한다(안 입는 경우도 하나의 경우의 수로 추가)
    }
    
    return answer-1; //모두 안 입는 경우인 1가지 빼고 반환
}