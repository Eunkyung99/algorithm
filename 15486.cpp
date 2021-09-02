#include <iostream>
#include <algorithm>
using namespace std;

//segmentation fault 전역변수로 선언! 
int T[1500001];
int P[1500001];
int dp[1500001];

int main(){
    int N;
    int MAX = 0;
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> T[i] >> P[i];
    }
    
    for(int i=1; i<=N+1; i++){
        //이전에 최댓값이 있을 수 있음
        if(MAX < dp[i-1]){
            MAX = dp[i-1];
        }

        int complete = i + T[i];
        if(complete > N+1){
            continue;
        }

        if(MAX > dp[i]){
            dp[i] = MAX;
        }

        dp[complete] = max(dp[i]+P[i], dp[complete]);
        
    }

    cout << dp[N+1]<<" ";
    

    return 0;
}