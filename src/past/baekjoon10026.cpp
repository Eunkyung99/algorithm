#include <iostream>
using namespace std;

int vi[4]={0, 0, -1, 1};
int vj[4]={1, -1, 0, 0};
int n;

void dfs_noblind(char color[][100], int visited[][100], int i, int j, char c){ //색맹 아닌 경우
	visited[i][j]=1; //방문 표시
	for(int k=0; k<4; k++){
		int ni=i+vi[k];
		int nj=j+vj[k];
		if(0<=ni && ni<n && 0<=nj && nj<n){ //범위 안에 존재
			if(color[ni][nj]==c && visited[ni][nj]==0) //인접한 칸과 색이 같고 방문하지 않으면
				dfs_noblind(color, visited, ni, nj, c); //재귀
		}
	}
}
void dfs_blind(char color[][100], int visited[][100], int i, int j, char c){ //색맹인 경우
	visited[i][j]=1;
	for(int k=0; k<4; k++){
		int ni=i+vi[k];
		int nj=j+vj[k];
		if(0<=ni && ni<n && 0<=nj && nj<n){
			if(c=='R'){ //c가 R일 때
				if((color[ni][nj]=='R'||color[ni][nj]=='G') && visited[ni][nj]==0) //인접한 칸이 R 또는 G인 경우
					dfs_blind(color, visited, ni, nj, 'R'); //c를 R로 하여 dfs_blind 실행
			}
			else{ //c가 B일 때
				if(color[ni][nj]=='B' && visited[ni][nj]==0) //인접한 칸이 B인 경우
					dfs_blind(color, visited, ni, nj, 'B'); //c를 B로 하여 dfs_blind 실행
			}
		}
	}
}

int main(){
	int noblindness=0, blindness=0;
	char color[100][100];
	int visited[100][100]={0,};
	cin>>n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin>>color[i][j]; //한 글자씩 입력받기
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){ //색맹이 아닌 경우에 대해 방문하지 않은 점 찾기
			if(color[i][j]=='R' && visited[i][j]==0){ //시작점이 R일 때
				dfs_noblind(color, visited, i, j, 'R');
				noblindness++; //구역 증가
			}
			if(color[i][j]=='G' && visited[i][j]==0){ //시작점이 G일 때
				dfs_noblind(color, visited, i, j, 'G');
				noblindness++; //구역 증가
			}
			if(color[i][j]=='B' && visited[i][j]==0){ //시작점이 B일 때
				dfs_noblind(color, visited, i, j, 'B');
				noblindness++; //구역 증가
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			visited[i][j]=0; //방문기록 초기화
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){ //색맹인 경우에 대해 방문하지 않은 점 찾기
			if((color[i][j]=='R' || color[i][j]=='G') && visited[i][j]==0){ //시작점이 R 또는 G일 때
				dfs_blind(color, visited, i, j, 'R'); //c를 R로 하여 dfs_noblind 호출
				blindness++; //구역 증가
			}
			if(color[i][j]=='B' && visited[i][j]==0){ //시작점이 B일 때
				dfs_blind(color, visited, i, j, 'B'); //c를 B로 하여 dfs_noblind 호출
				blindness++; //구역 증가
			}
		}
	}

	cout<<noblindness<<" "<<blindness<<endl;
	return 0;
}
