#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int n, Q;
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int A[65][65]; //******************** 100으로 하면 시간초과****** memset 많이 해서 그런듯
int tmp[65][65];
int N;
int total = 0, maxIce = 0;

void Rotate(int r, int c, int l){
    memset(tmp, 0, sizeof(tmp));
    //r,c / r+l-1, c / r, c+l-1 / r+l-1, c+l-1
    int nc = c + l - 1; //마지막 열
    for(int i=r; i<r+l; i++){
        int nr = r; //시작 행부터
        for(int j=c; j<c+l; j++){
            tmp[nr][nc] = A[i][j];
            nr++; //아래로 이동
        }
        nc--;
    }
    for(int i=r; i<r+l; i++){
        for(int j=c; j<c+l; j++){
            A[i][j] = tmp[i][j];
        }
    }
}

void Divide(int l){
    for(int i=0; i<N; i+=l){
        for(int j=0; j<N; j+=l){
            //i, j가 시작점
            Rotate(i, j, l);
        }
    }
}

void Minus(){
    memset(tmp, 0, sizeof(tmp));
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int cnt = 0; //인접 얼음 개수
            for(int d=0; d<4; d++){
                int nr = i + dr[d];
                int nc = j + dc[d];
                if((0<=nr && nr<N && 0<=nc && nc<N) && A[nr][nc]>0){
                    cnt += 1;
                }
            }
            if(cnt < 3 && A[i][j]>0){ //*******A[i][j]에서 뺄 게 남아있어야 함 - 얼음 존재 여부 검사 중요
                tmp[i][j] = A[i][j] - 1;
            }else{
                tmp[i][j] = A[i][j]; //유지 ****
            }
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            A[i][j] = tmp[i][j];
        }
    }
}

void BFS(){
    bool visited[100][100] = {false,};
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            total += A[i][j];
            if(!visited[i][j] && A[i][j] > 0){ //********* 그룹에는 얼음이 존재해야 함
                int group = 0;
                queue<pair<int, int> > q;
                visited[i][j] = true;
                q.push(make_pair(i, j));
                while(!q.empty()){
                    pair<int, int> p = q.front();
                    q.pop();
                    group += 1; //pop할 때마다 개수
                    int r = p.first;
                    int c = p.second;
                    for(int nd=0; nd<4; nd++){
                        int nr = r + dr[nd];
                        int nc = c + dc[nd];
                        if(0<=nr && nr<N && 0<=nc && nc<N && !visited[nr][nc]){
                            visited[nr][nc] = true; //가지치기 - 얼음이 없는 인접한 칸에 미리 방문 표시
                            if(A[nr][nc]>0){
                                q.push(make_pair(nr, nc));
                            }
                        }
                    }
                }
                if(group > maxIce){
                    maxIce = group;
                }
            }
        }
    }
}

int main(){
    int x;
    cin >> n >> Q;
    N=(1<<n); //**** for문 안 써도 됨

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> A[i][j];
        }
    }

    for(int i=0; i<Q; i++){
        cin >> x;
        Divide(1<<x);
        Minus();
    }

    BFS();

    cout << total <<"\n" << maxIce <<"\n";
    
    return 0;
}