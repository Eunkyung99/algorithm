#include <iostream>
using namespace std;
#define MAX 1000000
int min(int a, int b){ //�ּڰ� ���ϱ�
	return a>b?b:a;
}
int main(){
	int x;
	int DP[MAX]={0,};
	cin>>x;
	for(int i=2; i<=x; i++){ //DP[0]=DP[1]=0
		DP[i]=DP[i-1]+1; //�־��� ��� ���� ���(1 ���� ��� �ּ� Ƚ��)
		if(i%2==0) //2�� ������ ���
			DP[i]=min(DP[i], DP[i/2]+1);
		if(i%3==0) //3���� ������ ���
			DP[i]=min(DP[i], DP[i/3]+1);
	}

	cout<<DP[x];

	return 0;
}
