#include <iostream>
using namespace std;

int N, M;
int room[51][51];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int cleaning = 0;

void Clean(int r, int c, int d){
    //현재 위치 청소
    if(room[r][c] == 0){
        room[r][c] = 2; //청소 표시
        cleaning++;
    }
    
    for(int i=0; i<4; i++){
        d = (d - 1 + 4) % 4; //왼쪽 방향 전환
        int nr = r + dr[d];
        int nc = c + dc[d];
        if((0<=nr && nr<N && 0<=nc && nc<M) && room[nr][nc]==0){
            Clean(nr, nc, d);
            return; //******* 방향을 찾으면 리턴해줘야 함!!!
        }
    }

    //네 방향 모두 청소가 이미 되어 있거나 벽인 경우
    int backR = r - dr[d];
    int backC = c - dc[d];
    if((0<=backR && backR<N && 0<=backC && backC<M) && room[backR][backC]!=1){
        Clean(backR, backC, d);
        return; //******* 방향을 찾으면 리턴해줘야 함!!!
    }
    return;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int r, c, d;

    cin >> N >> M;
    cin >> r >> c >> d;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> room[i][j];
        }
    }

    Clean(r, c, d);

    cout << cleaning <<"\n";

    return 0;
}