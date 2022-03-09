#include <iostream>
#include <queue>
using namespace std;

int main(){
	int box[1001][1001];
	int visited[1001][1001];
	int n, m, max=0;
	int vi[4]={0, 0, 1, -1}; //상하
	int vj[4]={-1, 1, 0, 0}; //좌우
	queue<pair<int, int>> q;
	cin>>m>>n;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin>>box[i][j];
			visited[i][j]=-1;
			if(box[i][j]==1){
				q.push({i, j}); //익은 토마토의 위치 삽입
				visited[i][j]=0;
			}
		}
	}
	while(!q.empty()){ //큐가 빌 때까지 반복
		int i=q.front().first;
		int j=q.front().second;
		q.pop();
		for(int k=0; k<4; k++){
			int ni=i+vi[k];
			int nj=j+vj[k];
			if(0<=ni && ni<n && 0<=nj && nj<m){
				if(box[ni][nj]==0 && visited[ni][nj]==-1){
					visited[ni][nj]=visited[i][j]+1;
					q.push({ni, nj});
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(box[i][j]==0 && visited[i][j]==-1){
				cout<<"-1";
				return 0;
			}
			if(max<visited[i][j])
				max=visited[i][j];
		}
	}
	cout<<max;
	return 0;
}
