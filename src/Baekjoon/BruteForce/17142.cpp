#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int lab[51][51] = {0,};
int visited[51][51] = {-1,};
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<pair<int, int> > virus;
int wall = 0;
int minTime = 999999;

void Calculate(int flag){
    memset(visited, -1, sizeof(visited));
    int spread=0, last=0;
    queue<pair<pair<int, int>, int> > q;

    //& 연산 ***********************************
    for(int j=0; j<virus.size(); j++){
        if(flag & (1 << j)){
            int r = virus[j].first;
            int c = virus[j].second;
            visited[r][c] = 0;
            q.push(make_pair(make_pair(r, c), 0));
        }
    }

    while(!q.empty()){
        pair<pair<int, int>, int> p = q.front();
        q.pop();
        int r = p.first.first;
        int c = p.first.second;
        if(spread == (N*N - wall)){
            if(minTime > last){
                minTime = last;
            }
            break;
        }
        for(int d=0; d<4; d++){
            int nr = r + dr[d];
            int nc = c + dc[d];
            if(0<=nr && nr<N && 0<=nc && nc<N && (visited[nr][nc] == -1) && (lab[nr][nc]!=1)){
                if(lab[nr][nc] == 0){ //******* 활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다.
                    spread += 1;
                }
                visited[nr][nc] = p.second + 1;
                q.push(make_pair(make_pair(nr, nc), p.second+1));
                last = p.second+1;
            }
        }
    }
}
void DFS(int idx, int flag){
    int cnt = 0;
    // int f = flag;
    // while(f > 0){ ///**************** & 연샨으로도 구현 가능
    //     if(f % 2 == 1){
    //         cnt += 1;
    //     }
    //     f = f >> 1;
    // }
    //& 연산
    for(int j=0; j<virus.size(); j++){
        if(flag & (1 << j)){
            cnt += 1;
        }
    }
    if(cnt == M){ Calculate(flag); }

    for(int x=idx+1; x<virus.size(); x++){
        DFS(x, flag | (1 << x)); //선택하는 경우
        // DFS(x, flag); //선택 안 하는 경우 ****** 필요 없음!
    }
}

int main(){
    cin >> N >> M;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> lab[i][j];
            if(lab[i][j] == 2){
                virus.push_back(make_pair(i, j));
                wall += 1;
            }else if(lab[i][j] == 1){
                wall += 1;
            }
        }
    }

    DFS(-1, 0);

    if(minTime == 999999){
        cout << "-1\n";
    }else{
        cout << minTime <<"\n";
    }

    return 0;
}