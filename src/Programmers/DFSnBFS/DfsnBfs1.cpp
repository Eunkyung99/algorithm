#include <string>
#include <vector>

using namespace std;

int answer = 0;

void dfs(int idx, int result, vector<int> n, int t){
    if(idx == n.size()){
        if(result == t){
            answer += 1;
        }
        return;
    }
        
        //+-*/
        dfs(idx+1, result + n[idx], n, t);
        dfs(idx+1, result - n[idx], n, t);
    
}

int solution(vector<int> numbers, int target) {
    
    dfs(0, 0, numbers, target);
    
    return answer;
}