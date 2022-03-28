#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int turn = 0;
    int totalW = 0;
    queue<int> q;
    
    while(turn < truck_weights.size()){
        if(totalW + truck_weights[turn] <= weight){ //올라갈 수 있다면 turn번째 트럭 올리기
            q.push(truck_weights[turn]);
            totalW += truck_weights[turn];
            turn++;
        }else{
            q.push(0);
        }
        
        if(q.size() == bridge_length){ //bridge_length 초가 지났다면
            totalW -= q.front();
            q.pop();
        }
        answer ++;
        if(turn == truck_weights.size()){
            //마지막 트럭 올라갔다면
            answer += bridge_length;
            break;
        }
    }
    
    
    return answer;
}