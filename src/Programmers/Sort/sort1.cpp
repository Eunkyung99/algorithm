#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for(int v=0; v<commands.size(); v++){
        vector<int> tmp;
        int i = commands[v][0] - 1;
        int j = commands[v][1];
        int k = commands[v][2] - 1;
        for(int x=i; x<j; x++){
            tmp.push_back(array[x]);
        }
        sort(tmp.begin(), tmp.end());
        answer.push_back(tmp[k]);
    }
    return answer;
}