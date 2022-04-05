#include <iostream>
#include <cstring>
using namespace std;

int N, M, T;
int circle[51][51];
bool hasToBeErased[51][51];

void Rotate(int x, int d, int k){
    if(d==0){
        for(int i=0; i<k; i++){
            int top = circle[x][M];
            for(int j=M; j>1; j--){ //*******
                circle[x][j] = circle[x][j-1];
            }
            circle[x][1] = top;
        }
    }else{
        for(int i=0; i<k; i++){
            int top = circle[x][1];
            for(int j=1; j<M; j++){
                circle[x][j] = circle[x][j+1];
            }
            circle[x][M] = top;
        }
    }
}

void Check(int x){
    memset(hasToBeErased, false, sizeof(hasToBeErased));
    // bool erased[51] = {false};
    bool erased = false; //****** 원판 전체에서 인접한 수 있는지 검사
    int total = 0; //********* 원판 전체에 남아있는 수들의 평균
    int count = 0;
    for(int i=1; i<=N; i++){ //x의 배수(x는 2 이상)
        for(int j=1; j<=M; j++){
            if(circle[i][j] != 0){ //수가 있다면
                total += circle[i][j];
                count += 1;

                if(i>1){ //아래에 접한 것 확인
                    if(circle[i][j] == circle[i-1][j]){
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i-1][j] = true;
                    }    
                }
                if(i<N){ //위에 접한 것 확인
                    if(circle[i][j] == circle[i+1][j]){
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i+1][j] = true;
                    }
                }
                //좌우 접한 것 확인
                if(j==1){
                    if(circle[i][j] == circle[i][j+1]){
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i][j+1] = true;
                    }
                    if(circle[i][j] == circle[i][M]){ 
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i][M] = true;
                    }
                }else if(j==M){
                    if(circle[i][j] == circle[i][j-1]){
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i][j-1] = true;
                    }
                    if(circle[i][j] == circle[i][1]){  
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i][1] = true;
                    }
                }else{
                    if(circle[i][j] == circle[i][j-1]){
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i][j-1] = true;
                    }
                    if(circle[i][j] == circle[i][j+1]){
                        erased = true;
                        hasToBeErased[i][j] = true;
                        hasToBeErased[i][j+1] = true;
                    }
                }
            }
        }
    }

    if(!erased){ //********** 마지막에 한 번만 검사
        float avg = float(total) / float(count); //*********** 평균 버림 없어야 함!!
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                if(circle[i][j] != 0){ //*********** 없어진 수에는 더하는 거 아님!!
                    if(circle[i][j] > avg){
                        circle[i][j] -= 1;
                    }else if(circle[i][j] < avg){
                        circle[i][j] += 1;
                    }
                }
            }
        }
    }else{
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                if(hasToBeErased[i][j]){
                    circle[i][j] = 0;
                }
            }
        }
    }
}
int main(){
    int x, d, k;
    int ans = 0;
    cin >> N >> M >> T;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            cin >> circle[i][j];
        }
    }
    for(int i=0; i<T; i++){
        cin >> x >> d >> k;
        for(int y=x; y<=N; y+=x){
            Rotate(y, d, k);
        }
        Check(x);
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            ans += circle[i][j];
        }
    }

    cout << ans <<"\n";

    return 0;
}