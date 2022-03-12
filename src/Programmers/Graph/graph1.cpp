#include <string>
#include <vector>
#include <queue>

using namespace std;


int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    int maxL;
    vector<vector<int> > graph(n+1); //***
    int dist[20001] = {0,};
    
    for(int i=0; i<edge.size(); i++){
        int a = edge[i][0];
        int b = edge[i][1];
        graph[a].push_back(b); //벡터로 구현하면 전체 노드 조회할 필요 없음
        graph[b].push_back(a);

    }
    
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    
    while(!q.empty()){
        int s = q.front();
        q.pop();
        for(int i=0; i<graph[s].size(); i++){
            if(dist[graph[s][i]] == 0){ //방문 안 했다면 
                maxL = dist[graph[s][i]] = dist[s] + 1;
                q.push(graph[s][i]);
            }
        }
    }
    
    for(int i=2; i<=n; i++){
        if(dist[i] == maxL){
            answer += 1;
        }
    }
    
    return answer;
}