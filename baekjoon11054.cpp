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
		uplength[i]=1; //1로 초기화
		downlength[i]=1; //1로 초기화
	}
	for(int i=1; i<n; i++){ //앞에서 뒤로(길이가 가장 긴 증가하는 수열)
		for(int j=0; j<i; j++) //인덱스 i보다 작은 경우
			if(A[j]<A[i]){ //A[i]보다 값이 작은 원소이면
				if(uplength[j]+1>uplength[i]){ //길이가 증가할 수 있는지 확인
					uplength[i]=uplength[j]+1; //길이 증가
				}
			}
	}
	for(int i=n-2; i>=0; i--){ //뒤에서 앞으로(길이가 가장 긴 감소하는 수열)
			for(int j=n-1; j>i; j--) //인덱스 i보다 큰 경우
				if(A[j]<A[i]){ //A[i]보다 값이 작은 원소이면
					if(downlength[j]+1>downlength[i]){ //길이가 증가할 수 있는지 확인
						downlength[i]=downlength[j]+1; //길이 증가
					}
				}
		}
	for(int i=0; i<n; i++){
		sum[i]=uplength[i]+downlength[i]; //sum에 증가수열의 값과 감소수열의 값의 합 대입
	}
	for(int i=0; i<n; i++){
		if(max<sum[i])
			max=sum[i]; //sum 중에서 최댓값 찾기
	}
	cout<<max-1; //자기자신을 두 번 세기 때문에 -1한 결과 출력
	return 0;
}
