#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

priority_queue<int, vector<int>, greater<int> > pq;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    for(int i=0; i<scoville.size(); i++){
        pq.push(scoville[i]);
    }
    while(pq.top() < K){ //문제 조건 : 모든 음식의 스코빌 지수가 K 이상이 되도록
        int m1, m2, k;
        if(pq.size() == 1){
            answer = -1;
            break;
        }
        m1 = pq.top();
        pq.pop();
        m2 = pq.top();
        pq.pop();
        k = m1 + (m2 * 2);
        answer++; //섞음
        pq.push(k);
    }
    
    return answer;
}