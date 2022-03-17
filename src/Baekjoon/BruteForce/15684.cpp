#include <iostream>
using namespace std;

int N, M, H;
int answer = 9;
int ladder[31][11]={0,};
bool checkAble(){
    for(int J=1; J<=N; J++){ //**** i랑 j 헷갈리지 않기!! N이 열, H가 행!!!!
        int j = J;
        int i = 1;
        while(i<=H){ //***** 마지막 H행 사다리까지 검사해야 함!!
            if(ladder[i][j-1]==1){ //왼쪽
                j=j-1;
            }else if(ladder[i][j]==1){ //오른쪽
                j=j+1;
            }
            i+=1;
        }
        if(j!=J){
            return false;
        }
    }
    return true;
}

void Backtrack(int r, int c, int cnt){
    if(cnt > 3){
        return;
    }
    if(checkAble()){
        answer = answer > cnt ? cnt : answer;
        return;
    }
    for(int i=r; i<=H; i++){ //***** 무조건 (1,1) 부터 탐색하면 시간초과
        for(int j=1; j<N; j++){ //********** j=c부터가 아니라 1부터!!
            if(ladder[i][j] == 0){
                ladder[i][j] = 1;
                Backtrack(i, j, cnt+1);
                ladder[i][j] = 0; //원상복구
            }
        }
    }
}

int main(){
    cin >> N >> M >> H;
    int a, b;
    for(int i=0; i<M; i++){
        cin >> a >> b;
        ladder[a][b] = 1; //왼쪽에 표시
    }
    Backtrack(1, 1, 0);
    if(answer == 9){
        cout <<"-1\n";
    }else{
        cout << answer <<"\n";
    }
    return 0;
}