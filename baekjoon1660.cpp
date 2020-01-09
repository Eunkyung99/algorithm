#include <iostream>
using namespace std;
int main(){
	int n;
	int t[1000000]={0,};
	cin>>n;
	for(int i=0; t[i]<=300000; i++){
		t[i]=i*(i+1)*(i+2)/6;
	}

	return 0;
}
