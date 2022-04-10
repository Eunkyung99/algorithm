#include <iostream>
using namespace std;

struct Shark{
    int r, c;
    int dir;
    int priority[5][5];
    bool live;
};

struct Smell{
    int sharkN;
    int timeLeft;
};

int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};

int N, M, k;
int board[21][21];
Shark shark[401];
Smell smell[21][21];
Smell willbeAdd[21][21];
int dead = 0;

void Move(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){ //** willbeAdd 초기화 
            willbeAdd[i][j].sharkN = 0;
            willbeAdd[i][j].timeLeft = 0; 
        }
    }

    for(int i=M; i>0; i--){
        if(shark[i].live){
            bool move = false;
            int r = shark[i].r;
            int c = shark[i].c;
            int dir = shark[i].dir;
            for(int d=1; d<=4; d++){
                int nd = shark[i].priority[dir][d];
                int nr = r + dr[nd];
                int nc = c + dc[nd];
                if(0<=nr && nr<N && 0<=nc && nc<N){
                    if(smell[nr][nc].timeLeft == 0){
                        if(willbeAdd[nr][nc].sharkN > 0){ //이미 있을 경우
                            //있던 거 내쫓아야 함
                            int sharkNum = willbeAdd[nr][nc].sharkN;
                            shark[sharkNum].live = false; //죽음으로 바꾸기
                            dead += 1;
                        }
                        willbeAdd[nr][nc].sharkN = i;
                        willbeAdd[nr][nc].timeLeft = k;

                        shark[i].r = nr; //**** 새로운 정보 갱신
                        shark[i].c = nc;
                        shark[i].dir = nd;

                        move = true;
                        break;
                    }
                }
            }
            if(!move){
                for(int d=1; d<=4; d++){
                    int nd = shark[i].priority[dir][d];
                    int nr = r + dr[nd];
                    int nc = c + dc[nd];
                    if(0<=nr && nr<N && 0<=nc && nc<N){
                        if(smell[nr][nc].sharkN == i){
                            if(willbeAdd[nr][nc].sharkN > 0){ //이미 있을 경우
                                //있던 거 내쫓아야 함
                                int sharkNum = willbeAdd[nr][nc].sharkN;
                                shark[sharkNum].live = false; //죽음으로 바꾸기
                                dead += 1;
                            }
                            willbeAdd[nr][nc].sharkN = i;
                            willbeAdd[nr][nc].timeLeft = k;

                            shark[i].r = nr; //**** 새로운 정보 갱신
                            shark[i].c = nc;
                            shark[i].dir = nd;

                            break;
                        }
                    }
                }
            }
        }
    }

    //************************* 일단 현재 상황에서 다음 이동할 자리를 찾고 냄새 남은 시간 감소시켜야 함 ******
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(smell[i][j].timeLeft > 0){
                smell[i][j].timeLeft -= 1; //1초 지남 - 기존 감소시킴
                if(smell[i][j].timeLeft == 0){
                    smell[i][j].sharkN = 0; //sharkN도 초기화 
                }
            }
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(willbeAdd[i][j].timeLeft > 0){
                smell[i][j].sharkN = willbeAdd[i][j].sharkN;
                smell[i][j].timeLeft = willbeAdd[i][j].timeLeft;
            }
        }
    }
}

int main(){
    int ans = 0;
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> k;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
            if(board[i][j] > 0){
                shark[board[i][j]].r = i;
                shark[board[i][j]].c = j;
                smell[i][j].sharkN = board[i][j];
                smell[i][j].timeLeft = k;
            }
        }
    }

    for(int i=1; i<=M; i++){
        cin >> shark[i].dir;
        shark[i].live = true;
    }

    for(int i=1; i<=M; i++){
        for(int j=1; j<=4; j++){
            for(int k=1; k<=4; k++){
                cin >> shark[i].priority[j][k];
            }
        }
    }

    while(1){
        if(ans > 1000){
            ans = -1;
            break;
        }
        if(dead == M-1){
            break;
        }
        // if(shark[2].live == false){ //******* 2번이 항상 마지막에 죽는다는 보장 없음********
        //     break;
        // }
        Move();
        ans += 1;
    }

    cout << ans <<"\n";
    return 0;
}