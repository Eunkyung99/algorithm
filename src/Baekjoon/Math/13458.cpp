#include <iostream>
using namespace std;

int main(){
    int N;
    int A[1000000];
    int B, C;

    long long coach = 0; //*** long long 틀렸습니다!!

    cin >> N;
    for(int i=0; i<N; i++){
        cin >> A[i];
    }
    cin >> B >> C;

    coach = N; //최소 총감독관 한 명씩 필요 

    for(int i=0; i<N; i++){
        A[i] -= B;
        if(A[i] < 0){ A[i] = 0; }
        if(A[i]%C == 0){
            coach += A[i]/C;
        }else{
            coach += (A[i]/C + 1);
        }
    }

    cout << coach <<"\n";

    return 0;
}