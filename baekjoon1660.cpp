#include <iostream>
using namespace std;
int main(){
	int n, j=0, sum=0;
	int t[1000];
	int dp[333333]; //*배열의 크기
	cin>>n;
	for(int i=0; sum<=n; i++){ //합이 n보다 작을 때 반복
		sum=t[j++]=i*(i+1)*(i+2)/6; //제곱수들의 합 저장
	}
	for(int i=0; i<=n; i++){
		dp[i]=999999; //큰 수를 기본값으로 저장
	}
	for(int i=0; i<j; i++){ //이때 j는 t 배열의 마지막 값
		dp[t[i]]=1; //제곱수의 합에 해당하는 dp=1
		for(int k=t[i]; k<=n; k++) //i까지의 제곱수의 합
			dp[k]=dp[k]>dp[k-t[i]]+1?dp[k-t[i]]+1:dp[k]; //제곱수의 합에 해당하는 dp 값+1이 더 작으면 바꿔준다.
	}
	cout<<dp[n];
	return 0;
}
