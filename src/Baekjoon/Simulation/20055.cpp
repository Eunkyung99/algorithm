#include <iostream>
#include <vector>
using namespace std;

int A[201] = {0,};
int robot[201] = {0,};
int N, K;

int main(){
    int turn = 0;
    bool flag = true;
    cin >> N >> K;
    for(int i=1; i<=2*N; i++){
        cin >> A[i];
    }

    while(flag){
        int cnt = 0;
        turn += 1;

        //Rotate
        int tmp = A[2*N];
        for(int i=2*N; i>1; i--){ 
            A[i] = A[i-1];
        }
        A[1] = tmp;

        for(int i=N; i>0; i--){ //******* 1~N칸만 검사하면 됨 로봇이 존재할 수 있는 공간 잘 생각하기
            robot[i] = robot[i-1]; 
            if(robot[N] == 1){ //**************** 내리는 칸에 먼저 도달할 수 있는 경우는 여기에도 있음
                robot[N] = 0;
            }
        }

        //Robot Move
        for(int i=N-1; i>0; i--){
            if(robot[i]){ //현재 칸에 로봇 존재해야 함
                if((A[i+1]>0) && (robot[i+1]==0)){ //다음 칸 조건 검사
                    robot[i] = 0;
                    robot[i+1] = 1;
                    A[i+1] -= 1;
                    if(i+1 == N){
                        robot[i+1] = 0;
                    }
                }
            }
        }

        //Put on Robot
        if(A[1] != 0){
            A[1] -= 1;
            robot[1] = 1;
        }

        for(int i=1; i<=2*N; i++){
            if(A[i] == 0){
                cnt += 1;
            }
            if(cnt >= K){
                flag = false;
                break;
            }
        }
    }

    cout << turn <<"\n";

    return 0;
}