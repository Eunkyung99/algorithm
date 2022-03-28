#include <iostream>
#include <cstring>
using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int R, C, T;
int room[51][51];
int moves[51][51];

int airR = -1;
int airC = 0;

void Spread(){
    memset(moves, 0, sizeof(moves));
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if(room[r][c] > 0){ //미세먼지가 있는 칸
                int cnt = 0;
                int amount = room[r][c]/5;
                for(int d=0; d<4; d++){
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if((0<=nr && nr<R && 0<=nc && nc<C) && !((nr==airR && nc==0) || (nr==airR+1 && nc==0))){
                        moves[nr][nc] += amount;
                        cnt += 1;
                    }
                }
                room[r][c] -= amount*cnt;
            }
        }
    }
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            room[r][c] += moves[r][c];
        }
    }
}

void AirClear(){
    //upper
    for(int r=airR-1; r>0; r--){
        room[r][0] = room[r-1][0];
    }
    for(int c=0; c<C-1; c++){
        room[0][c] = room[0][c+1];
    }
    for(int r=0; r<airR; r++){
        room[r][C-1] = room[r+1][C-1];
    }
    for(int c=C-1; c>0; c--){
        room[airR][c] = room[airR][c-1];
    }
    //bottom
    for(int r=airR+2; r<R-1; r++){
        room[r][0] = room[r+1][0];
    }
    for(int c=0; c<C-1; c++){
        room[R-1][c] = room[R-1][c+1];
    }
    for(int r=R-1; r>airR+1; r--){
        room[r][C-1] = room[r-1][C-1];
    }
    for(int c=C-1; c>0; c--){
        room[airR+1][c] = room[airR+1][c-1];
    }
}

int main(){
    int ans = 0;
    cin >> R >> C >> T;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> room[i][j];
            if(room[i][j]==-1){
                if(airR == -1){
                    airR = i;
                }
                room[i][j] = 0;
                room[i][j] = 0;
            }
        }
    }

    for(int t=0; t<T; t++){
        Spread();
        AirClear();
    }

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(room[i][j] > 0){
                ans += room[i][j];
            }
        }
    }

    cout << ans <<"\n";

    return 0;
}