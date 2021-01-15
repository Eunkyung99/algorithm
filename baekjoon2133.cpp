#include <iostream>
using namespace std;
int main(){
	int n;
	int dp[31]={0,};
	cin>>n;
	dp[0]=1;
	if(n%2==0){
		for(int i=2; i<=n; i+=2){ //bottom-up 방식
			dp[i]=3*dp[i-2];
			for(int j=4; j<=i; j+=2){ //i보다 작은 짝수 인덱스
				dp[i]+=2*dp[i-j]; //dp[j]*dp[i=j] 경우의 수
			}
		}
		cout<<dp[n];
	}
	else{ //n은 홀수여야 함
		cout<<0;
	}
	return 0;
}
