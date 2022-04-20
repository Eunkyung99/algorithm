#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int R, C, K;
int office[21][21];
vector<vector<pair<int, int> > > heater(5);
vector<pair<int, int> > v;
int temperature[21][21] = {0,};
int increase[21][21] = {0,};
//오 왼 위 아래
int dr[5] = {0, 0, 0, -1, 1};
int dc[5] = {0, 1, -1, 0, 0};

int wall1[21][21] = {0,}; //위/아래
int wall2[21][21] = {0,}; //왼/오

void Add(){
    for(int r=1; r<=R; r++){
        for(int c=1; c<=C; c++){
            temperature[r][c] += increase[r][c];
        }
    }
}

void Wind(int r, int c, int d, int amount){
    if(amount == 0){ return; }
    increase[r][c] = amount;
    
    int nr, nc, checkR, checkC;
    nr = r + dr[d];
    nc = c + dc[d];
    if(1<=nr && nr<=R && 1<=nc && nc<=C){
        if(d<=2){ //좌우
            int wallC = c < nc ? c : nc; //더 왼쪽인 열 찾기
            int wallR = c < nc ? r : nr;
            if(!wall2[wallR][wallC]){ //벽이 없으면
                Wind(nr, nc, d, amount-1);
            }
        }else{ //상하
            int wallR = r < nr ? r : nr; //더 위인 행 찾기
            int wallC = r < nr ? c : nc;
            if(!wall1[wallR][wallC]){ //벽이 없으면
                Wind(nr, nc, d, amount-1);
            }
        }
    }

    nr = r + dr[d] + dc[d]; //90도 회전
    nc = c + dc[d] + dr[d];
    checkR = nr - dr[d]; //사이에 끼어있는 칸
    checkC = nc - dc[d];
    if(1<=nr && nr<=R && 1<=nc && nc<=C){
        if(d<=2){ //좌우
            int wall2C = checkC < nc ? checkC : nc;
            int wall2R = checkC < nc ? checkR : nr;

            int wall1R = checkR < r ? checkR : r;
            int wall1C = checkR < r ? checkC : c; 
            if(!wall2[wall2R][wall2C] && !wall1[wall1R][wall1C]){
            // if(!(wall2[checkR][checkC] && wall2[nr][nc]) && !(wall1[checkR][checkC] && wall1[r][c])){
                Wind(nr, nc, d, amount-1);
            }
        }else{ //상하
            int wall1R = checkR < nr ? checkR : nr;
            int wall1C = checkR < nr ? checkC : nc;

            int wall2C = checkC < c ? checkC : c; 
            int wall2R = checkR < r ? checkR : r;
            if(!wall1[wall1R][wall1C] && !wall2[wall2R][wall2C]){
            // if(!(wall1[checkR][checkC] && wall1[nr][nc]) && !(wall2[checkR][checkC] && wall2[r][c])){
                Wind(nr, nc, d, amount-1);
            }
        }
    }

    nr = r + dr[d] - dc[d]; //270도 회전
    nc = c + dc[d] - dr[d]; 
    checkR = nr - dr[d];
    checkC = nc - dc[d];
    if(1<=nr && nr<=R && 1<=nc && nc<=C){
        if(d<=2){ //좌우
            int wall2C = checkC < nc ? checkC : nc;
            int wall2R = checkC < nc ? checkR : nr;

            int wall1R = checkR < r ? checkR : r;
            int wall1C = checkR < r ? checkC : c; 
            if(!wall2[wall2R][wall2C] && !wall1[wall1R][wall1C]){
            // if(!(wall2[checkR][checkC] && wall2[nr][nc]) && !(wall1[checkR][checkC] && wall1[r][c])){
                Wind(nr, nc, d, amount-1);
            }
        }else{ //상하
            int wall1R = checkR < nr ? checkR : nr;
            int wall1C = checkR < nr ? checkC : nc;

            int wall2C = checkC < c ? checkC : c; 
            int wall2R = checkR < r ? checkR : r;
            if(!wall1[wall1R][wall1C] && !wall2[wall2R][wall2C]){
            // if(!(wall1[checkR][checkC] && wall1[nr][nc]) && !(wall2[checkR][checkC] && wall2[r][c])){
                Wind(nr, nc, d, amount-1);
            }
        }
    }
}

int main(){
    int W, x, y, t;
    int chocolate = 0;
    cin >> R >> C >> K;
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++){
            cin >> office[i][j];
            if(0<office[i][j] && office[i][j]<5){
                heater[office[i][j]].push_back(make_pair(i, j));
            }else if(office[i][j] == 5){
                v.push_back(make_pair(i, j));
            }
        }
    }
    cin >> W;
    for(int i=0; i<W; i++){
        cin >> x >> y >> t;
        if(t==0){
            // wall1[x][y] = 1; //*****************양쪽에 표시하면 겹칠 수 있는 문제 발생 -> 한쪽에만 표시하고 한쪽만 검사!!!!
            wall1[x-1][y] = 1; //위에 표시
        }else{
            wall2[x][y] = 1; //왼쪽에 표시
            // wall2[x][y+1] = 1; 
        }
    }

    while(1){
        if(chocolate > 100){
            chocolate = 101;
            break;
        }

        //1단계
        for(int h=1; h<=4; h++){
            for(int i=0; i<heater[h].size(); i++){
                memset(increase, 0, sizeof(increase));
                pair<int, int> p = heater[h][i];
                int r = p.first;
                int c = p.second;

                int nr = r + dr[h];
                int nc = c + dc[h];
                if(1<=nr && nr<=R && 1<=nc && nc<=C){
                    Wind(nr, nc, h, 5);
                }
                //하나의 히터에서 더해지는 increase 값 저장되어 있음
                Add();
            }
        }

        //2단계 - 온도 조절
        memset(increase, 0, sizeof(increase));
        for(int r=1; r<=R; r++){
            for(int c=1; c<=C; c++){
                for(int d=1; d<=4; d++){
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if((1<=nr && nr<=R && 1<=nc && nc<=C) && (temperature[r][c] > temperature[nr][nc])){
                        //벽도 없어야 함
                        if(d<=2){
                            int wallC = c < nc ? c : nc;
                            int wallR = c < nc ? r : nr;
                            if(wall2[wallR][wallC]){ continue; }
                        }else{
                            int wallR = r < nr ? r : nr;
                            int wallC = r < nr ? c : nc;
                            if(wall1[wallR][wallC]){ continue; }
                        }
                        int amount = (temperature[r][c] - temperature[nr][nc])/4;
                        increase[r][c] -= amount;
                        increase[nr][nc] += amount;
                    }
                }
            }
        }
        Add();

        //3단계 - 테두리 온도 감소
        for(int c=1; c<=C; c++){
            if(temperature[1][c] > 0){
                temperature[1][c] -= 1;
            }
            if(temperature[R][c] > 0){
                temperature[R][c] -= 1;
            }
        }
        for(int r=2; r<R; r++){
            if(temperature[r][1] > 0){
                temperature[r][1] -= 1;
            }
            if(temperature[r][C] > 0){
                temperature[r][C] -= 1;
            }
        }

        //4단계 - 초콜릿 먹기
        chocolate += 1;

        int check = 0;
        for(int k=0; k<v.size(); k++){
            int r = v[k].first;
            int c = v[k].second;
            if(temperature[r][c] >= K){
                check += 1;
            }
        }
        if(check == v.size()){
            break;
        }
    }

    cout << chocolate <<"\n";

    return 0;
}