#include <iostream>
#include <algorithm>
using namespace std;
int info[1001];
int dp[3][1001][32];
int main(){
	int t, w;
	int m=0;
	cin>>t>>w;
	for(int i=1; i<=t; i++){
		cin>>info[i];
	}
	for(int i=1; i<=t; i++){ //i에 대한 최적의 해를 구함
		for(int j=1; j<=w+1; j++){
			if(info[i]==1){ //i초에 1번 트리에서 떨어질 때
				dp[1][i][j]=max(dp[2][i-1][j-1]+1, dp[1][i-1][j]+1); //2번에서 움직이거나 1번에서 그대로(i-1초에서) 있어서 자두 하나 더 받음
				dp[2][i][j]=max(dp[2][i-1][j], dp[1][i-1][j-1]); //1번에서 움직이거나 2번에서 그대로 있고 자두 받지 않음
			}
			else{ //i초에 2번 트리에서 떨어질 때
				if(i==1 && j==1) //1초일 때 2번 트리에서 떨어졌을 때는 움직이기 위해(처음 시작 위치가 1)
					continue;
				dp[1][i][j]=max(dp[2][i-1][j-1], dp[1][i-1][j]); //2번에서 움직이거나 1번에서 그대로 있고 자두 받지 않음
				dp[2][i][j]=max(dp[2][i-1][j]+1, dp[1][i-1][j-1]+1); //1번에서 움직이거나 2번에서 그대로 있고 자두 받음
			}
		}
	}
	for(int i=1; i<=w+1; i++){
		m=max(m, max(dp[1][t][i], dp[2][t][i]));
	}
	cout<<m;
	return 0;
}
