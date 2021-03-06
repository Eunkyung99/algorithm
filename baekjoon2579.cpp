/*
 계단 오르기 게임은 계단 아래 시작점부터 계단 꼭대기에 위치한 도착점까지 가는 게임이다. <그림 1>과 같이 각각의 계단에는 일정한 점수가 쓰여 있는데 계단을 밟으면 그 계단에 쓰여 있는 점수를 얻게 된다.
 계단 오르는 데는 다음과 같은 규칙이 있다.

계단은 한 번에 한 계단씩 또는 두 계단씩 오를 수 있다. 즉, 한 계단을 밟으면서 이어서 다음 계단이나, 다음 다음 계단으로 오를 수 있다.
연속된 세 개의 계단을 모두 밟아서는 안 된다. 단, 시작점은 계단에 포함되지 않는다.
마지막 도착 계단은 반드시 밟아야 한다.
따라서 첫 번째 계단을 밟고 이어 두 번째 계단이나, 세 번째 계단으로 오를 수 있다. 하지만, 첫 번째 계단을 밟고 이어 네 번째 계단으로 올라가거나, 첫 번째, 두 번째, 세 번째 계단을 연속해서 모두 밟을 수는 없다.

각 계단에 쓰여 있는 점수가 주어질 때 이 게임에서 얻을 수 있는 총 점수의 최댓값을 구하는 프로그램을 작성하시오.
첫째 줄에 계단 오르기 게임에서 얻을 수 있는 총 점수의 최댓값을 출력한다.
 */
#include <iostream>
using namespace std;
int max(int a, int b){
	return (a>b)?a:b;
}
int main(){
	int n;
	int stair[10000]={0,};
	int dp[10000][2]={0,}; //2차원 배열 사용(전에 밟은 계단이 한 칸 아래(1)인지 두칸 아래(0)인지 구분)
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>stair[i]; //계단 입력
	}
	dp[1][1]=dp[1][0]=stair[1]; //첫번째 계단까지의 최대점수=첫번째 계단 밟기
	dp[2][0]=stair[2]; //두번째 계단까지의 최대점수(두 칸 아래(0)인 경우)
	dp[2][1]=stair[1]+stair[2]; //두번째 계단까지의 최대 점수(한 칸 아래(1)인 경우)
	for(int i=3; i<=n; i++){ //n까지 dp 구하기
		dp[i][0]=stair[i]+max(dp[i-2][0], dp[i-2][1]); //i번째 계단을 밟기 전 i-2번째 계단을 밟음(i-2까지의 최댓값인 dp[i-2] 이용하여 해를 구함)
													   //이때는 i-2번 전에 i-3을 밟았던 i-4를 밟았던 상관 없으므로 두 값 중 큰 값을 더해줌
		dp[i][1]=stair[i]+dp[i-1][0]; //i번째 계단을 밟기 전 i-1번째 계단을 밟음
								 	  //이때는 i-1과 i를 밟으므로 i-2를 밟은 경우는 제외해야 함 따라서 dp[i-1][0]인 i-3->i-1->i인 경우만 값을 구해줌
	}
	cout<<max(dp[n][0], dp[n][1])<<endl; //dp[n]에 저장된 값들 중 최댓값 출력
	return 0;
}
//수행시간:O(n)
