#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M;
int office[9][9];

int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };

int emptyArea = 0; 
int ans = 0;
int called = 0;
vector<pair<int, int> > virus;
vector<pair<int, int> > candidate;

int Spread(){
    int visited[9][9] = {false,};
    int cnt = emptyArea - 3;
    for(int v=0; v<virus.size(); v++){
        queue<pair<int, int> > q;

        int vr = virus[v].first;
        int vc = virus[v].second;
        visited[vr][vc] = true;
        q.push(make_pair(vr, vc));

        while(!q.empty()){
            pair<int, int> p = q.front();
            q.pop();
            for(int d=0; d<4; d++){
                int nr = p.first + dr[d];
                int nc = p.second + dc[d];
                if((0<=nr && nr<N && 0<=nc && nc<M) && !visited[nr][nc] && office[nr][nc]==0){
                    q.push(make_pair(nr, nc));
                    visited[nr][nc] = true;
                    cnt -= 1; //virus 퍼진 것
                    if(cnt < ans){ //가지치기
                        return -1;
                    }
                }
            }
        }
    }
    return cnt;
}

void DFS(int idx, int built){
    if(built == 3){
        called += 1;
        int cnt = Spread();
        if(ans < cnt){
            ans = cnt;
        }
        return;
    }

    for(int i=idx+1; i<candidate.size(); i++){
        int nr = candidate[i].first;
        int nc = candidate[i].second;
        office[nr][nc] = 1;
        DFS(i, built+1);
        office[nr][nc] = 0;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> office[i][j];
            if(office[i][j] == 0){
                emptyArea += 1;
                candidate.push_back(make_pair(i, j));
            }
            if(office[i][j] == 2){
                virus.push_back(make_pair(i, j));
            }
        }
    }
    DFS(-1, 0);

    cout << ans <<"\n";
    return 0;
}