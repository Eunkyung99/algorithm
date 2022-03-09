#include <iostream>
using namespace std;
int main(){
	int n;
	int T[1000]={0,}; //배열의 범위 크게
	int P[1000]={0,};
	int dp[1000]={0,};
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>T[i];
		cin>>P[i];
	}
	for(int i=n; i>0; i--){
		if(i+T[i]>n+1){ //범위 초과
			dp[i]=dp[i+1]; //i+1까지의 최댓값
		}
		else{
			if(dp[i+1]<dp[i+T[i]]+P[i]){ //i일에 일을 하지 않는 경우와 일을 했을 경우
				dp[i]=dp[i+T[i]]+P[i]; //더 많이 버는 값을 dp[i]에 저장
			}
			else{
				dp[i]=dp[i+1]; //i일에 일을 안 하는 경우
			}
		}
	}
	cout<<dp[1]<<endl; //dp[1]이 최댓값
	return 0;
}
