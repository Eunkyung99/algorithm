#include <iostream>
using namespace std;
void escape(int n){
	bool open[n+1]={false,}; //���� �����ִ� ���·� �ʱ�ȭ
	int dp[n+1]={0,}; //dp�� 0���� �ʱ�ȭ
	for(int i=1; i<=n; i++){ //i ���� ����
		dp[i]=dp[i-1]; //dp[i-1] ���� dp[i]�� ���� ����
		for(int j=1; i*j<=n; j++){ //n������ i����� �� �湮
			if(open[i*j]==true){ //���� �������� ��
				open[i*j]=false; //�� �ݰ�
				dp[i]-=1; //Ż�� ������ ��� -1
			}
			else{ //���� �������� ��
				open[i*j]=true; //�� ����
				dp[i]+=1; //Ż�� ������ ���+1
			}
		}
	}
	cout<<dp[n]<<endl; //dp[n]�� n������� �������� �� Ż�� ������ ���
}
int main(){
	int testcase;
	int tc[100000]; //100���� �������� �� ��Ÿ�ӿ���
	cin>>testcase;
	for(int i=0; i<testcase; i++){
		cin>>tc[i]; //n ����
	}
	for(int i=0; i<testcase; i++){
		escape(tc[i]); //������ n�鿡 ���� escape �Լ� ����
	}
	return 0;
}
