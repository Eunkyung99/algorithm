#include <iostream>
using namespace std;
int main(){
	int n, max=0;
	cin>>n;
	int T[n+1];
	int P[n+1];
	int dp[n+1]={0,};
	for(int i=1; i<=n; i++){
		cin>>T[i];
		cin>>P[i];
	}
	for(int i=2; i<=n; i++){
		for(int j=1; j<=i-1; j++){
			if(i-j>=T[j]){
				if(dp[i]<dp[j]+P[i]){
					dp[i]=dp[j]+P[i];
				}
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(i+T[i]<=n+1){
			if(max<dp[i])
				max=dp[i];
		}
	}
	cout<<max;
	return 0;
}
