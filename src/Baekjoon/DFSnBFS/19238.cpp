//로직이 어렵지 않았지만 오래걸림 ㅅㅂ
//바뀌는 값을 계속 우선순위큐에 넣어서 오류나고
//우선순위큐랑 큐는 pop하면 리턴값 없음 주의^^^
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int taxiR, taxiC, fuel;
int road[21][21];
int map[21][21];
int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};
int m = 0; // 태운 승객 수

struct Guest{
    int startR, startC;
    int destR, destC;
    int dist;
};
Guest g[401];

struct compare{
    bool operator()(const Guest& a, const Guest& b){
        if(a.dist == b.dist){
            if(a.startR == b.startR){
                return a.startC > b.startC; //****** 부등호 반대!!
            }
            return a.startR > b.startR;
        }
        return a.dist > b.dist;
    }
};

bool moveGuest(Guest nextG){
    bool canBeArrived = false;
    bool visited[21][21] = {false,};
    queue<Guest> q;
    taxiR = nextG.startR;
    taxiC = nextG.startC;
    fuel -= nextG.dist;
    visited[taxiR][taxiC] = true;

    Guest taxi;
    taxi.startR = taxiR;
    taxi.startC = taxiC;
    taxi.dist = 0;

    q.push(taxi);

    while(!q.empty()){
        Guest t = q.front();
        int r = t.startR;
        int c = t.startC;
        int d = t.dist;
        q.pop();
        if(nextG.destR == t.startR && nextG.destC == t.startC){
            if(fuel - t.dist >= 0){ //태우기 성공
                fuel += t.dist;
                map[nextG.startR][nextG.startC] = 0; //승객 표시 지우기!!
                taxiR = nextG.destR;
                taxiC = nextG.destC;
                canBeArrived = true;
                m += 1; //승객 이동 완료
            }
            break;
        }
        for(int i=0; i<4; i++){
            int nr = r + dr[i]; //********* t.startR이 계속 바뀌므로 접근 주의!! 미리 저장필요
            int nc = c + dc[i];
            if((1<=nr && nr<=N && 1<=nc && nc<=N) && (road[nr][nc]==0) && (!visited[nr][nc])){
                t.startR = nr;
                t.startC = nc;
                t.dist = d+1;
                q.push(t);
                visited[nr][nc] = true;
            }
        }
    }
    
    return canBeArrived;
}

bool FindGuest(){
    //taxiR, taxiC;
    bool visited[21][21] = {false,}; //********
    Guest taxi;
    taxi.startR = taxiR;
    taxi.startC = taxiC;
    taxi.dist = 0;
    visited[taxiR][taxiC] = true;

    priority_queue<Guest, vector<Guest>, compare> pq;
    queue<Guest> q;
    q.push(taxi);

    while(!q.empty()){
        Guest t = q.front();
        q.pop(); //******************** Guest t = q.pop() - 당연히 에러.. no viable conversion void .. ㅅㅂ
        int r = t.startR;
        int c = t.startC;
        int d = t.dist; //********
        if(map[r][c] > 0){ //승객이 기다리고 있으면
            g[map[r][c]].dist = t.dist; //******
            pq.push(g[map[r][c]]); //해당 승객 정보 넣음
        }
        for(int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if((1<=nr && nr<=N && 1<=nc && nc<=N) && (road[nr][nc]==0) && (!visited[nr][nc])){
                t.startR = nr;
                t.startC = nc;
                // t.dist += 1; //********** 계속 증가돼서 i가 다음인 경우에 더 증가된 거리가 들어감
                t.dist = d+1;
                q.push(t);
                visited[nr][nc] = true;
            }
        }
    }

    if(!pq.empty()){
        Guest nextG = pq.top(); //****** 
        pq.pop(); //이 승객을 태울 것
        if(fuel - nextG.dist > 0){ //태울 수 있음
            if(moveGuest(nextG)){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    //다음 승객이 없음
    return false;
}
int main(){
    int startR, startC, destR, destC;

    cin >> N >> M >> fuel;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> road[i][j];
        }
    }

    cin >> taxiR >> taxiC;

    for(int i=1; i<=M; i++){
        cin >> startR >> startC >> destR >> destC;
        g[i].startR = startR;
        g[i].startC = startC;
        g[i].destR = destR;
        g[i].destC = destC;
        map[startR][startC] = i; //승객이 기다리고 있는 곳만 표시!
    }

    while(1){
        bool ret = FindGuest();
        if(!ret){
            break;
        }
    }

    if(m==M){
        cout << fuel <<"\n";
    }else{
        cout << "-1\n";
    }

    return 0;
}