#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

vector<int> board[5][5];
vector<int> moving[5][5];
int smell[5][5];
vector<int> tmp[5][5];
bool visited[5][5];

int M, S;
int sharkR, sharkC;
//0 1 2 3 4 5 6 7 
//← ↖ ↑ ↗ → ↘ ↓ ↙ 
int dr[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dc[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int maxDead = 0;
int minRoute = 9999;

void MoveShark(int r, int c, int cnt, int route, int dead){
    if(cnt == 3){
        if(dead > maxDead){
            maxDead = dead;
            minRoute = route;
        }else if(dead == maxDead && route < minRoute){
            minRoute = route;
        }
        return;
    }
    for(int d=0; d<8; d+=2){
        int nr = r + dr[d];
        int nc = c + dc[d];
        if(1<=nr && nr<=4 && 1<=nc && nc<=4){ //************** 갔던데 또 가도 됨. 하지만 물고기 개수는 중복 카운트 불가!!!!
            //상1 좌2 하3 우4
            int val;
            if(d==2){ val = 1; } //상
            else if(d==4){ val = 4; } //우
            else if(d==6){ val = 3; } //하
            else{ val = 2; }
            int ten = 1;
            for(int x=0; x<2-cnt; x++){
                ten *= 10; //자릿수 찾기
            }
            if(!visited[nr][nc]){ //***********
                visited[nr][nc] = true;
                MoveShark(nr, nc, cnt+1, route+val*ten, dead+board[nr][nc].size());
                visited[nr][nc] = false;
            }else{ 
                MoveShark(nr, nc, cnt+1, route+val*ten, dead);
            }
        }
    }
}
int main(){
    cin >> M >> S;
    int x, y, d;
    for(int i=0; i<M; i++){
        cin >> x >> y >> d;
        board[x][y].push_back(d-1); //방향 1~8 -> 0~7
    }
    cin >> sharkR >> sharkC;

    for(int p=1; p<=S; p++){
        // //1단계
        for(int i=1; i<=4; i++){
            for(int j=1; j<=4; j++){
                // for(int s=0; s<board[i][j].size(); s++){
                //     tmp[i][j].push_back(board[i][j][s]);
                // }
                tmp[i][j] = board[i][j]; //******************** 벡터의 복사
            }
        }

        //2단계
        for(int i=1; i<=4; i++){
            for(int j=1; j<=4; j++){
                for(int s=board[i][j].size()-1; s>=0; s--){
                    int d = board[i][j][s];
                    for(int k=0; k<8; k++){ //최대 8번
                        int nr = i + dr[d];
                        int nc = j + dc[d];
                        if((1<=nr && nr<=4 && 1<=nc && nc<=4) && smell[nr][nc]==0 && !(nr==sharkR && nc==sharkC)){
                            moving[nr][nc].push_back(d);
                            board[i][j].erase(board[i][j].begin()+s);
                            break; 
                        }else{
                            d = (d+7) % 8;
                        }
                        //이동 못 하는 경우 ***********
                        if(k==7){
                            moving[i][j].push_back(d); //******************** 이동 못 하므로 nr, nc말고 i, j에 넣어줘야 함!!
                            board[i][j].erase(board[i][j].begin()+s);
                        }
                    }
                }
            }
        }

        for(int i=1; i<=4; i++){
            for(int j=1; j<=4; j++){
                for(int s=moving[i][j].size()-1; s>=0; s--){
                    board[i][j].push_back(moving[i][j][s]);
                    moving[i][j].erase(moving[i][j].begin()+s);
                }
            }
        }

        //3단계
        minRoute = 99999, maxDead = 0;
        memset(visited, false, sizeof(visited));
        // visited[sharkR][sharkC] = true;
        MoveShark(sharkR, sharkC, 0, 0, 0);
        //minRoute가 결정됨
        int ten = 100;
        for(int i=0; i<3; i++){
            int d = minRoute / (ten);
            minRoute %= ten;
            ten /= 10;

            if(d==1){ d=2; } //상
            else if(d==2){ d=0; } //좌
            else if(d==3){ d=6; } //하
            else{ d=4; } //우
            sharkR += dr[d];
            sharkC += dc[d];
            if(board[sharkR][sharkC].size() > 0){ //**************물고기가 있던 칸에만 냄새 증가!!!
                smell[sharkR][sharkC] = p; //현재 턴으로 남김
            }
            board[sharkR][sharkC].clear();
        }
            
        //4단계
        if(p>2){
            for(int i=1; i<=4; i++){
                for(int j=1; j<=4; j++){
                    if(smell[i][j] == p-2){
                        smell[i][j] = 0;
                    }
                }
            }
        }

        //5단계
        for(int i=1; i<=4; i++){
            for(int j=1; j<=4; j++){
                for(int s=tmp[i][j].size()-1; s>=0; s--){
                    board[i][j].push_back(tmp[i][j][s]);
                    tmp[i][j].erase(tmp[i][j].begin()+s);
                }
            }
        }
    }
    int ans = 0;
    for(int i=1; i<=4; i++){
        for(int j=1; j<=4; j++){
            ans += board[i][j].size();
        }
    }

    cout << ans <<"\n";

    return 0;
}