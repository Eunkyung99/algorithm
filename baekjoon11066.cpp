#include <iostream>
using namespace std;
int min(int a, int b){
	return a<b?a:b;
}
int main(){
	int testcase;
	cin>>testcase;
	for(int tc=0; tc<testcase; tc++){
		int n;
		cin>>n;
		int cost[n+1]={0,};
		int dp[n+1][n+1]={0,};
		for(int i=1; i<=n; i++){
			cin>>cost[i]; //비용 입력받고
			cost[i]+=cost[i-1]; //비용 누적 계산
		}
		for(int end=1; end<n; end++){
			for(int i=1; i<=n-end; i++){
				dp[i][i+end]=999999999; //최댓값으로 먼저 설정해줌
				for(int mid=i; mid<i+end; mid++){
					dp[i][i+end]=min(dp[i][i+end], dp[i][mid]+dp[mid+1][i+end]); //중간에 자를 수 있는 모든 구간들의 최소 dp 값을 더해줌
				}
				dp[i][i+end]+=cost[i+end]-cost[i-1]; //i부터 i+end까지의 비용 더해줌
			}
		}
		cout<<dp[1][n]<<endl; //정답 출력
	}
	return 0;
}
