#include <iostream>
using namespace std;
int main(){
	int n;
	int T[1000]={0,}; //�迭�� ���� ũ��
	int P[1000]={0,};
	int dp[1000]={0,};
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>T[i];
		cin>>P[i];
	}
	for(int i=n; i>0; i--){
		if(i+T[i]>n+1){ //���� �ʰ�
			dp[i]=dp[i+1]; //i+1������ �ִ�
		}
		else{
			if(dp[i+1]<dp[i+T[i]]+P[i]){ //i�Ͽ� ���� ���� �ʴ� ���� ���� ���� ���
				dp[i]=dp[i+T[i]]+P[i]; //�� ���� ���� ���� dp[i]�� ����
			}
			else{
				dp[i]=dp[i+1]; //i�Ͽ� ���� �� �ϴ� ���
			}
		}
	}
	cout<<dp[1]<<endl; //dp[1]�� �ִ�
	return 0;
}
