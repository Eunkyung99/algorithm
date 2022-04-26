#include <iostream>
using namespace std;

int N;
int A[12];
int op[4];

long minimum = 1000000005;
long maximum = -1000000005; //************* 음수!!

void DFS(long res, int idx){
    if(idx == N){
        if(minimum > res){
            minimum = res;
        }
        if(maximum < res){
            maximum = res;
        }
        return;
    }
    int num = A[idx];

    for(int i=0; i<4; i++){
        if(op[i] > 0){
            op[i] -= 1;
            if(i==0){
                DFS(res+num, idx+1);
            }else if(i==1){
                DFS(res-num, idx+1);
            }else if(i==2){
                DFS(res*num, idx+1);
            }else{
                DFS(res/num, idx+1);
            }
            op[i] += 1; //원상복귀
        }
    }
}

int main(){
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> A[i];
    }
    for(int i=0; i<4; i++){
        cin >> op[i];
    }

    DFS(A[0], 1);

    cout << maximum <<"\n" << minimum <<"\n";

    return 0;
}