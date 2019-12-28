#include <iostream>
using namespace std;

void dfs(int box[][1000], int i, int j, int n, int m){
	int vi[4]={0, 0, -1, 1}; //상하
	int vj[4]={-1, 1, 0, 0}; //좌우
	for(int k=0; k<4; k++){
		int ni=i+vi[k]; //새로운 행 인덱스
		int nj=j+vj[k]; //새로운 열 인덱스
		if(0<=ni && ni<n && 0<=nj && nj<m){ //새로운 인덱스가 범위 안에 있고 미방문
			if(box[ni][nj]==0){ //값이 0이면(익지 않은 상태, 미방문)
				box[ni][nj]=box[i][j]+1; //현재 값+1(최소 2)
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
