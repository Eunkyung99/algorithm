#include <string>
#include <vector>

using namespace std;

int A[5] = {1, 2, 3, 4, 5};
int B[8] = {2, 1, 2, 3, 2, 4, 2, 5};
int C[10] = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    int cA = 0;
    int cB = 0;
    int cC = 0;
    for(int v=0; v<answers.size(); v++){
        if(A[v%5] == answers[v]){
            cA++;
        }
        if(B[v%8] == answers[v]){
            cB++;
        }
        if(C[v%10] == answers[v]){
            cC++;
        }
    }
    
    int maxAns = max(max(cA, cB), cC);
    
    if(maxAns == cA){
        answer.push_back(1);
    }
    if(maxAns == cB){
        answer.push_back(2);
    }
    if(maxAns == cC){
        answer.push_back(3);
    }
    return answer;
}