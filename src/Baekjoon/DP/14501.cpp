#include <iostream>
#include <algorithm>
using namespace std;

int N;
int T[16], P[16];
int dp[16] = {0,};
int ans = 0;

int main(){
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> T[i] >> P[i];
    }

    for(int i=1; i<=N; i++){
        if(dp[i-1] > dp[i]){
            dp[i] = dp[i-1];
        }
        if(i+T[i] <= N+1){
            dp[i+T[i]] = max(dp[i+T[i]], dp[i]+P[i]);
            if(dp[i+T[i]] > ans){
                ans = dp[i+T[i]];
            }
        }
    }
    cout << ans <<"\n";

    return 0;
}