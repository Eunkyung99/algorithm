#include <iostream>
using namespace std;

int dr[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dc[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

struct Fish{
    int r;
    int c;
    int dir;
    bool live;
};
Fish f[17];

int ocean[4][4];
int ans = 0;

void moveFish(){
    for(int i=1; i<=16; i++){
        if(!f[i].live){
            continue; //************* 죽으면 넘어가기 !!!!
        }
        int r = f[i].r;
        int c = f[i].c;
        int d = f[i].dir;
        for(int j=0; j<8; j++){
            int nr = r + dr[d];
            int nc = c + dc[d];
            if(0<=nr && nr<4 && 0<=nc && nc<4){
                if(ocean[nr][nc] == 0){
                    //이동 - 물고기가 죽어있거나 없는 상태
                    ocean[r][c] = 0;
                    ocean[nr][nc] = i;
                    f[i].r = nr;
                    f[i].c = nc;
                    f[i].dir = d;
                    break;
                }else if(ocean[nr][nc] > 0){
                    //교환 - 물고기가 살아있다는 의미
                    int tmp = ocean[nr][nc];
                    Fish tmpF = f[tmp];
                    f[tmp].r = r;
                    f[tmp].c = c;
                    // f[tmp].dir = d; ******************** 방향은 교환하는 것 아님!!!!
                    ocean[r][c] = tmp;

                    f[i].r = nr; 
                    f[i].c = nc; 
                    f[i].dir = d;
                    ocean[nr][nc] = i;
                    break;
                }
            }
            d = (d%8) + 1; //*****
        }
    }
}

void Copy_State(int temp[4][4], int orig[4][4], Fish t[17], Fish o[17]){ //******* 맵 2개 상태 임시 저장하는 함수 만들기!!!
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            temp[i][j] = orig[i][j];
        }
    }

    for(int i=1; i<=16; i++){
        t[i] = o[i];
    }
}

void DFS(int sharkR, int sharkC, int sharkD, int ate){ //******* dfs로 구현하는 거 생각하기!!!
    if(ate > ans){ ans = ate; }
    
    int temp_map[4][4];
    Fish temp_fish[17];

    Copy_State(temp_map, ocean, temp_fish, f); 

    moveFish();
    
    for(int i=1; i<=3; i++){
        int nr = sharkR + dr[sharkD]*i; //******* i 곱해야 함
        int nc = sharkC + dc[sharkD]*i;
        if(0<=nr && nr<4 && 0<=nc && nc<4){
            if(ocean[nr][nc]>0){ //물고기가 있으면
                int dead = ocean[nr][nc];
                int nd = f[dead].dir;
                ocean[sharkR][sharkC] = 0; //상어 있던 자리 초기화
                ocean[nr][nc] = -1; //상어 표시
                f[dead].live = false;

                DFS(nr, nc, nd, ate+dead); //위에 상태에서 다음 DFS 진행!!!
                //원상복구 ******* -> 다음 상어 이동방식 계산
                ocean[nr][nc] = dead;
                ocean[sharkR][sharkC] = -1;
                f[dead].live = true;
            }
        }
    }

    Copy_State(ocean, temp_map, f, temp_fish); //********* 처음 DFS 호출했을 때로 맵 되돌리기
}
int main(){
    int sharkR, sharkC, sharkD;
    int a, b;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cin >> a >> b;
            ocean[i][j] = a; //a번 물고기 위치 표시
            f[a].r = i;
            f[a].c = j;
            f[a].dir = b;
            f[a].live = true;
        }
    }

    sharkR = sharkC = 0;
    int ate = ocean[sharkR][sharkC]; //0,0
    ocean[sharkR][sharkC] = -1;
    sharkD = f[ate].dir;
    f[ate].live = false;

    DFS(sharkR, sharkC, sharkD, ate);

    cout << ans <<"\n";

    return 0;
}