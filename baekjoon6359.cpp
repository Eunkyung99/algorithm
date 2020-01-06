#include <iostream>
using namespace std;
void escape(int n){
	bool open[n+1]={false,}; //문이 닫혀있는 상태로 초기화
	int dp[n+1]={0,}; //dp는 0으로 초기화
	for(int i=1; i<=n; i++){ //i 라운드 실행
		dp[i]=dp[i-1]; //dp[i-1] 값을 dp[i]에 먼저 저장
		for(int j=1; i*j<=n; j++){ //n이하의 i배수인 방 방문
			if(open[i*j]==true){ //문이 열려있을 때
				open[i*j]=false; //문 닫고
				dp[i]-=1; //탈출 가능한 사람 -1
			}
			else{ //문이 닫혀있을 때
				open[i*j]=true; //문 열고
				dp[i]+=1; //탈출 가능한 사람+1
			}
		}
	}
	cout<<dp[n]<<endl; //dp[n]이 n라운드까지 실행했을 때 탈출 가능한 사람
}
int main(){
	int testcase;
	int tc[100000]; //100으로 설정했을 때 런타임에러
	cin>>testcase;
	for(int i=0; i<testcase; i++){
		cin>>tc[i]; //n 저장
	}
	for(int i=0; i<testcase; i++){
		escape(tc[i]); //저장한 n들에 대해 escape 함수 실행
	}
	return 0;
}
