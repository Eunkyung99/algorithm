#include <iostream>
using namespace std;
int main(){
	int n, j=0, sum=0;
	int t[1000];
	int dp[333333]; //*�迭�� ũ��
	cin>>n;
	for(int i=0; sum<=n; i++){ //���� n���� ���� �� �ݺ�
		sum=t[j++]=i*(i+1)*(i+2)/6; //���������� �� ����
	}
	for(int i=0; i<=n; i++){
		dp[i]=999999; //ū ���� �⺻������ ����
	}
	for(int i=0; i<j; i++){ //�̶� j�� t �迭�� ������ ��
		dp[t[i]]=1; //�������� �տ� �ش��ϴ� dp=1
		for(int k=t[i]; k<=n; k++) //i������ �������� ��
			dp[k]=dp[k]>dp[k-t[i]]+1?dp[k-t[i]]+1:dp[k]; //�������� �տ� �ش��ϴ� dp ��+1�� �� ������ �ٲ��ش�.
	}
	cout<<dp[n];
	return 0;
}
