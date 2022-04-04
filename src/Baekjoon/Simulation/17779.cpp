#include <iostream>
#include <cstring>
using namespace std;

int N;
int city[21][21];
bool boundary[21][21];
int people[5];
int total = 0;
int ans = 99999999;

void Find(int x, int y, int d1, int d2){
    memset(boundary, false, sizeof(boundary));
    memset(people, 0, sizeof(people));
    //경계 표시
    int x1 = x, y1 = y;
    int x2 = x, y2 = y;
    int x3 = x+d1, y3 = y-d1;
    int x4 = x+d2, y4 = y+d2;
    for(int i=0; i<=d1; i++){
        boundary[x1][y1] = true;
        x1 += 1;
        y1 -= 1;
        
        boundary[x4][y4] = true;
        x4 += 1;
        y4 -= 1;
    }

    for(int i=0; i<=d2; i++){
        boundary[x2][y2] = true;
        x2 += 1;
        y2 += 1;

        boundary[x3][y3] = true;
        x3 += 1;
        y3 += 1;
    }

    for(int r=x+1; r<x+d1+d2; r++){ //********** 경계선 내부도 직접 표시해줘야 함!!!(5번)
        bool flag = false;
        for(int c=y-d1; c<=y+d2; c++){
            if(boundary[r][c]){
                flag = !flag;
            }
            if(flag){ boundary[r][c] = true; }
        }
    }

    //1번
    for(int r=1; r<x+d1; r++){
        for(int c=1; c<=y; c++){
            if(!boundary[r][c]){
                people[0] += city[r][c]; 
            }
        }
    }
    //2번
    for(int r=1; r<=x+d2; r++){
        for(int c=y+1; c<=N; c++){
            if(!boundary[r][c]){
                people[1] += city[r][c];
            }
        }
    }
    //3번
    for(int r=x+d1; r<=N; r++){
        for(int c=1; c<y-d1+d2; c++){
            if(!boundary[r][c]){
                people[2] += city[r][c];
            }
        }
    }
    //4번
    for(int r=x+d2+1; r<=N; r++){
        for(int c=y-d1+d2; c<=N; c++){
            if(!boundary[r][c]){
                people[3] += city[r][c];
            }
        }
    }
    //5번
    people[4] = total - (people[0] + people[1] + people[2] + people[3]);

    int maxP = 0, minP = 9999999; //**************** 최댓값 설정 잘 하자 100*4000
    for(int i=0; i<5; i++){
        if(people[i] < minP){
            minP = people[i];
        }
        if(people[i] > maxP){
            maxP = people[i];
        }
    }

    if(maxP - minP < ans){
        ans = maxP - minP;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> city[i][j];
            total += city[i][j];
        }
    }

    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            for(int d1=1; d1<N; d1++){
                for(int d2=1; d2<N; d2++){
                    if((x+d1+d2<=N) && (1<=y-d1) && (y+d2<=N)){
                        Find(x, y, d1, d2);
                    }
                } 
            }
        }
    }

    cout << ans << "\n";
    return 0;
}