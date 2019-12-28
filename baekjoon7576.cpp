#include <iostream>
using namespace std;

void dfs(int box[][1000], int i, int j, int n, int m){
	int vi[4]={0, 0, -1, 1}; //����
	int vj[4]={-1, 1, 0, 0}; //�¿�
	for(int k=0; k<4; k++){
		int ni=i+vi[k]; //���ο� �� �ε���
		int nj=j+vj[k]; //���ο� �� �ε���
		if(0<=ni && ni<n && 0<=nj && nj<m){ //���ο� �ε����� ���� �ȿ� �ְ� �̹湮
			if(box[ni][nj]==0){ //���� 0�̸�(���� ���� ����, �̹湮)
				box[ni][nj]=box[i][j]+1; //���� ��+1(�ּ� 2)
				dfs(box, ni, nj, n, m);
			}
			else{
				if(box[ni][nj]!=-1 && box[ni][nj]>box[i][j]+1){
					box[ni][nj]=box[i][j]+1;
					dfs(box, ni, nj, n, m);
				}
			}
		}
	}
}

int findminday(int box[][1000], int n, int m){
	int max=1;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(box[i][j]==0){
				return -1;
			}
			else{
				if(box[i][j]>max){
					max=box[i][j];
				}
			}
		}
	}
	return max-1;
}
int main(){
	int box[1000][1000];
	int n, m;
	cin>>m>>n;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			cin>>box[i][j];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(box[i][j]==1){
				dfs(box, i, j, n, m);
			}
		}
	}
	cout<<findminday(box, n, m);
	return 0;
}
