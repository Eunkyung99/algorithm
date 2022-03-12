#include <string>
#include <cstring>
#include <vector>

using namespace std;

int student[31];

int solution(int n, vector<int> lost, vector<int> reserve) {
    // memset(student, 0, sizeof(student));
    
    for(int s=0; s<=30; s++){
        student[s] = 1;
    }
    
    int answer = 0;
    for(int i=0; i<lost.size(); i++){
        student[lost[i]] -= 1;
    }
    for(int i=0; i<reserve.size(); i++){
        student[reserve[i]] += 1;
    }
    for(int s=1; s<=n; s++){
        if(student[s] == 0){
            if(student[s-1] > 1){
                student[s-1] -= 1;
                student[s] += 1;
            }else if(student[s+1] > 1){
                student[s+1] -= 1;
                student[s] += 1;
            }
        }
    }  
    for(int s=1; s<=n; s++){
        if(student[s] > 0){
            answer += 1;
        }
    }
    return answer;
}