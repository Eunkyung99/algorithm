#include <iostream>
using namespace std;
#define MAX 1000000
int min(int a, int b){ //최솟값 구하기
	return a>b?b:a;
}
int main(){
	int x;
	int DP[MAX]={0,};
	cin>>x;
	for(int i=2; i<=x; i++){ //DP[0]=DP[1]=0
		DP[i]=DP[i-1]+1; //최악의 경우 먼저 계산(1 빼는 경우 최소 횟수)
		if(i%2==0) //2로 나눠질 경우
			DP[i]=min(DP[i], DP[i/2]+1);
		if(i%3==0) //3으로 나눠질 경우
			DP[i]=min(DP[i], DP[i/3]+1);
	}

	cout<<DP[x];

	return 0;
}
