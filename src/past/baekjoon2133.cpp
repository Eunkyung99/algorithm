#include <iostream>
using namespace std;
int main(){
	int n;
	int dp[31]={0,};
	cin>>n;
	dp[0]=1;
	if(n%2==0){
		for(int i=2; i<=n; i+=2){ //bottom-up ���
			dp[i]=3*dp[i-2];
			for(int j=4; j<=i; j+=2){ //i���� ���� ¦�� �ε���
				dp[i]+=2*dp[i-j]; //dp[j]*dp[i=j] ����� ��
			}
		}
		cout<<dp[n];
	}
	else{ //n�� Ȧ������ ��
		cout<<0;
	}
	return 0;
}
