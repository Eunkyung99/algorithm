#include <iostream>
#include <vector>
using namespace std;
int N, M, K;
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct FireBall{
    int m, d, s;
};

vector<FireBall> board[51][51];

void Move(){
    vector<FireBall> temp[51][51];
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(board[i][j].size() > 0){
                for(int v=board[i][j].size()-1; v>=0; v--){
                    FireBall fb = board[i][j][v];
                    int nr = (i + fb.s*dr[fb.d])%N;
                    int nc = (j + fb.s*dc[fb.d])%N;
                    //****************************** 음수인 경우 N 더해주면 됨!*************
                    if(nr<=0){
                        nr += N;
                    }
                    if(nc<=0){
                        nc += N;
                    }
                    board[i][j].erase(board[i][j].begin()+v);
                    temp[nr][nc].push_back(fb);
                }
            }
        }
    }

    //temp에 모두 이동한 상태

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(temp[i][j].size() > 1){
                int totalC = 0;
                int totalS = 0;
                int totalM = 0;
                int cntD = 0;
                for(int v=0; v<temp[i][j].size(); v++){
                    totalS += temp[i][j][v].s;
                    totalM += temp[i][j][v].m;
                    totalC += 1;
                    if(temp[i][j][v].d%2==0){ //짝수 개수 셈
                        cntD += 1;
                    }
                }
                int avgM = totalM/5;
                if(avgM > 0){ //0이 되면 소멸
                    FireBall fb;
                    fb.m = avgM;
                    fb.s = totalS/totalC;
                    for(int x=0; x<4; x++){
                        if(cntD == 0 || cntD == totalC){ //짝수가 하나도 없거나 모두 짝수인 경우
                            fb.d = x*2;
                            board[i][j].push_back(fb);
                        }else{
                            fb.d = x*2+1;
                            board[i][j].push_back(fb);
                        }
                    }
                }
            }else if(temp[i][j].size() == 1){
                board[i][j].push_back(temp[i][j][0]);
            }
        }
    }
}

int main(){
    FireBall fb;
    int r, c;
    int ans = 0;
    cin >> N >> M >> K;
    for(int i=0; i<M; i++){
        cin >> r >> c >> fb.m >> fb.s >> fb.d;
        board[r][c].push_back(fb); 
    }

    for(int k=0; k<K; k++){
        Move();
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            for(int k=0; k<board[i][j].size(); k++){
                ans += board[i][j][k].m;
            }
        }
    }

    cout << ans <<"\n";

    return 0;
}