#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int N, L, R;
int A[51][51] = {0,};
int day = 0;

bool Move(){
    vector<pair<int, int> > v;
    bool isMoved = false;
    bool visited[51][51] = {false,};

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            //시작점 찾기
            if(visited[i][j]) continue;
            visited[i][j] = true;

            queue<pair<int, int> > q;
            q.push(make_pair(i, j));
            v.push_back(make_pair(i, j)); //연합된 나라 기록
            int total = A[i][j];

            while(!q.empty()){
                pair<int, int> p = q.front();
                q.pop();
                for(int d=0; d<4; d++){
                    int nr = p.first + dr[d];
                    int nc = p.second + dc[d];
                    if((0<=nr && nr<N && 0<=nc && nc<N) && !visited[nr][nc]){ //****** visited 검사 왜 안 해?;
                        int sub = abs(A[p.first][p.second] - A[nr][nc]);
                        if(L<=sub && sub<=R){
                            visited[nr][nc] = true; //연합
                            q.push(make_pair(nr, nc));
                            v.push_back(make_pair(nr, nc));
                            total += A[nr][nc];
                        }
                    }
                }
            }

            //인구 이동
            if(v.size() > 1){ //****** 1개는 무조건 들어감
                isMoved = true;
                int people = total / v.size();
                for(int x=0; x<v.size(); x++){
                    int r = v[x].first;
                    int c = v[x].second;
                    A[r][c] = people;
                }
            }
            v.clear(); //****** 1개는 무조건 들어감->무조건 클리어해줘야 함
        }
    }

    return isMoved;
}
int main(){
    cin >> N >> L >> R;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> A[i][j];
        }
    }
    
    while(1){
        if(!Move()) break;
        day+=1;
    }

    cout << day <<"\n";

    return 0;
}