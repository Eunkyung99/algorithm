#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int N;
int sea[21][21];
bool visited[21][21];
int sharkR, sharkC, sharkS;
int times = 0;
int ate = 0;

struct Coord{
    int r;
    int c;
    int distance;
};

struct compare{
    bool operator()(const Coord &a, const Coord &b){
        if(a.distance == b.distance){
            if(a.r == b.r){
                return a.c > b.c;
            }
            return a.r > b.r;
        }
        return a.distance > b.distance;
    }
};

bool move(){
    memset(visited, false, sizeof(visited));
    priority_queue<Coord, vector<Coord>, compare> pq;

    Coord co;
    co.r = sharkR;
    co.c = sharkC;
    co.distance = 0;
    pq.push(co);
    visited[sharkR][sharkC] = true;

    while(!pq.empty()){
        Coord coord = pq.top();
        pq.pop();

        if(sea[coord.r][coord.c] < sharkS && sea[coord.r][coord.c] > 0){ //먹을 수 있으면 ***** 0보다 커야 함!!
            sea[coord.r][coord.c] = 0;
            sharkR = coord.r;
            sharkC = coord.c;
            times += coord.distance;

            ate += 1;
            if(ate == sharkS){
                sharkS += 1;
                ate = 0;
            }

            return true;
        }

        for(int d=0; d<4; d++){
            int nr = coord.r + dr[d];
            int nc = coord.c + dc[d];
            if(0<=nr && nr<N && 0<=nc && nc<N && !visited[nr][nc] && sea[nr][nc]<=sharkS){
                visited[nr][nc] = true;
                Coord newC;
                newC.r = nr;
                newC.c = nc;
                newC.distance = coord.distance + 1;
                pq.push(newC);
            }
        }
    }

    //더 이상 먹을 수 있는 물고기가 없음
    return false;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> sea[i][j];
            if(sea[i][j] == 9){
                sea[i][j] = 0;
                sharkR = i;
                sharkC = j;
                sharkS = 2;
            }
        }
    }

    while(1){
        if(!move()){
            break;
        }
    }

    cout << times <<"\n";

    return 0;
}