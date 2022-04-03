#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int A[101][101] = {0,};
int cnt[101] = {0,};
int countR, countC;
struct Info{
    int num;
    int count;
};
struct compare{
    bool operator()(const Info& a, const Info& b){
        if(a.count == b.count){
            return a.num > b.num; //*******
        }
        return a.count > b.count; //********
    }
};
Info zero;

void R(){
    int maxC = 0; //***
    for(int r=1; r<=countR; r++){
        memset(cnt, 0, sizeof(cnt));
        for(int c=1; c<=countC; c++){
            cnt[A[r][c]] += 1;
        }
        Info info;
        priority_queue<Info, vector<Info>, compare> pq;
        for(int n=1; n<=100; n++){
            if(cnt[n] == 0){ continue; }
            info.num = n;
            info.count = cnt[n];
            pq.push(info);
        }
        for(int c=1; c<=100; c+=2){
            Info t = pq.top();
            pq.pop();
            A[r][c] = t.num;
            A[r][c+1] = t.count;
            if(pq.empty()){
                if((t.num != 0) && (maxC < c+1)){ //******* 0이 아닌거 확인 필요
                    maxC = c+1; //****** countC가 작아질 수 있지 않나..?
                }
                // break; //***** 나머지 자리 0으로 채워야 함   
                pq.push(zero); //****************
            }
        }
    }
    countC = maxC;
}

void C(){
    int maxR = 0;
    for(int c=1; c<=countC; c++){
        memset(cnt, 0, sizeof(cnt));
        for(int r=1; r<=countR; r++){
            cnt[A[r][c]] += 1;
        }
        Info info;
        priority_queue<Info, vector<Info>, compare> pq;
        for(int n=1; n<=100; n++){
            if(cnt[n] == 0){ continue; }
            info.num = n;
            info.count = cnt[n];
            pq.push(info);
        }
        for(int r=1; r<=100; r+=2){
            Info t = pq.top();
            pq.pop();
            A[r][c] = t.num;
            A[r+1][c] = t.count;
            if(pq.empty()){
                if((t.num!=0) && (maxR < r+1)){ //*********
                    maxR = r+1;
                }
                pq.push(zero); //***
            }
        }
    }
    countR = maxR;
}

int main(){
    int r, c, k;
    int time = 0;
    zero.num = 0;
    zero.count = 0;
    cin >> r >> c >> k;
    for(int i=1; i<=3; i++){
        for(int j=1; j<=3; j++){
            cin >> A[i][j];
        }
    }
    countR = countC = 3;
    while(A[r][c] != k){
        if(time == 100){
            time = -1;
            break;
        }
        if(countR >= countC){
            R();
        }else{
            C();
        }
        time += 1;
    }
    
    cout << time <<"\n";

    return 0;
}