#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> days;
    vector<int> answer;
    for(int i=0; i<progresses.size(); i++){
        int need = 100 - progresses[i];
        if(need % speeds[i] == 0){
            days.push_back(need/speeds[i]);
        }else{
            days.push_back(need/speeds[i] + 1);
        }
    }
    
    int before = 0;
    int v = -1; //index
    for(int i=0; i<days.size(); i++){
        if(before < days[i]){
            answer.push_back(1);
            v++; 
            before = days[i]; //갱신
        }else{
            answer[v] += 1;
        }
    }
    return answer;
}