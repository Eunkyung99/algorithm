#include <iostream>
using namespace std;

int main(){
	int A[1000]={0};
	int n, max=0;
	cin>>n;
	int uplength[n];
	int downlength[n];
	int sum[n];
	for(int i=0; i<n; i++)
		cin>>A[i];
	for(int i=0; i<n; i++){
		uplength[i]=1; //1�� �ʱ�ȭ
		downlength[i]=1; //1�� �ʱ�ȭ
	}
	for(int i=1; i<n; i++){ //�տ��� �ڷ�(���̰� ���� �� �����ϴ� ����)
		for(int j=0; j<i; j++) //�ε��� i���� ���� ���
			if(A[j]<A[i]){ //A[i]���� ���� ���� �����̸�
				if(uplength[j]+1>uplength[i]){ //���̰� ������ �� �ִ��� Ȯ��
					uplength[i]=uplength[j]+1; //���� ����
				}
			}
	}
	for(int i=n-2; i>=0; i--){ //�ڿ��� ������(���̰� ���� �� �����ϴ� ����)
			for(int j=n-1; j>i; j--) //�ε��� i���� ū ���
				if(A[j]<A[i]){ //A[i]���� ���� ���� �����̸�
					if(downlength[j]+1>downlength[i]){ //���̰� ������ �� �ִ��� Ȯ��
						downlength[i]=downlength[j]+1; //���� ����
					}
				}
		}
	for(int i=0; i<n; i++){
		sum[i]=uplength[i]+downlength[i]; //sum�� ���������� ���� ���Ҽ����� ���� �� ����
	}
	for(int i=0; i<n; i++){
		if(max<sum[i])
			max=sum[i]; //sum �߿��� �ִ� ã��
	}
	cout<<max-1; //�ڱ��ڽ��� �� �� ���� ������ -1�� ��� ���
	return 0;
}
