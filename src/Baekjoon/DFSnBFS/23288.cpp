#include <iostream>
#include <queue>
using namespace std;

int N, M, K;
int map[21][21];

int dr[4] = {0, 1, 0, -1}; //동남서북(시계)
int dc[4] = {1, 0, -1, 0};

int dice[7] = {0, 1, 2, 3, 4, 5, 6};

int diceR = 1, diceC = 1, diceD = 0;

void Right(){
    int tmp = dice[1];
    dice[1] = dice[4];
    dice[4] = dice[6];
    dice[6] = dice[3];
    dice[3] = tmp;
}

void Left(){
    int tmp = dice[1];
    dice[1] = dice[3];
    dice[3] = dice[6];
    dice[6] = dice[4];
    dice[4] = tmp;
}

void Up(){
    int tmp = dice[1];
    dice[1] = dice[5];
    dice[5] = dice[6];
    dice[6] = dice[2];
    dice[2] = tmp;
}

void Down(){
    int tmp = dice[1];
    dice[1] = dice[2];
    dice[2] = dice[6];
    dice[6] = dice[5];
    dice[5] = tmp;
}

int getScore(int r, int c){
    queue<pair<int, int> > q;
    bool visited[21][21] = {false,};
    int count = 0;
    int target = map[r][c];
    visited[r][c] = true;
    q.push(make_pair(r, c));
    while(!q.empty()){
        pair<int, int> p = q.front();
        q.pop();
        count += 1;
        for(int d=0; d<4; d++){
            int nr = p.first + dr[d];
            int nc = p.second + dc[d];
            if((1<=nr && nr<=N && 1<=nc && nc<=M) && !visited[nr][nc] && map[nr][nc] == target){ //**** 가로 길이 다름(M)
                visited[nr][nc] = true;
                q.push(make_pair(nr, nc));
            }
        }
    }
    return count*target;
}
int main(){
    int score = 0;
    cin >> N >> M >> K;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            cin >> map[i][j];
        }
    }

    for(int i=0; i<K; i++){
        int nr = diceR + dr[diceD];
        int nc = diceC + dc[diceD];
        if(1<=nr && nr<=N && 1<=nc && nc<=M){
            score += getScore(nr, nc);
            diceR = nr;
            diceC = nc;
            if(diceD == 0){ //****** 움직이는거 빼먹음
                Right(); 
            }else if(diceD == 1){
                Down();
            }else if(diceD == 2){
                Left();
            }else{
                Up();
            }
            if(dice[6] > map[nr][nc]){
                diceD = (diceD+1)%4;
            }else if(dice[6] < map[nr][nc]){
                diceD = (diceD+3)%4;
            }
        }else{ //맵 벗어난 경우 방향 전환
            diceD = (diceD+2)%4;
            nr = diceR + dr[diceD];
            nc = diceC + dc[diceD];
            if(diceD == 0){
                Right(); 
            }else if(diceD == 1){
                Down();
            }else if(diceD == 2){
                Left();
            }else{
                Up();
            }

            diceR = nr;
            diceC = nc;
            score += getScore(nr, nc);
            if(dice[6] > map[nr][nc]){
                diceD = (diceD+1)%4;
            }else if(dice[6] < map[nr][nc]){
                diceD = (diceD+3)%4;
            }
        }
    }

    cout << score << "\n";

    return 0;
}