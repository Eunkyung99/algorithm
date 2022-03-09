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
			cin>>cost[i]; //��� �Է¹ް�
			cost[i]+=cost[i-1]; //��� ���� ���
		}
		for(int end=1; end<n; end++){
			for(int i=1; i<=n-end; i++){
				dp[i][i+end]=999999999; //�ִ����� ���� ��������
				for(int mid=i; mid<i+end; mid++){
					dp[i][i+end]=min(dp[i][i+end], dp[i][mid]+dp[mid+1][i+end]); //�߰��� �ڸ� �� �ִ� ��� �������� �ּ� dp ���� ������
				}
				dp[i][i+end]+=cost[i+end]-cost[i-1]; //i���� i+end������ ��� ������
			}
		}
		cout<<dp[1][n]<<endl; //���� ���
	}
	return 0;
}
