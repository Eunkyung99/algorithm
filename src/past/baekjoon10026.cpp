#include <iostream>
using namespace std;

int vi[4]={0, 0, -1, 1};
int vj[4]={1, -1, 0, 0};
int n;

void dfs_noblind(char color[][100], int visited[][100], int i, int j, char c){ //���� �ƴ� ���
	visited[i][j]=1; //�湮 ǥ��
	for(int k=0; k<4; k++){
		int ni=i+vi[k];
		int nj=j+vj[k];
		if(0<=ni && ni<n && 0<=nj && nj<n){ //���� �ȿ� ����
			if(color[ni][nj]==c && visited[ni][nj]==0) //������ ĭ�� ���� ���� �湮���� ������
				dfs_noblind(color, visited, ni, nj, c); //���
		}
	}
}
void dfs_blind(char color[][100], int visited[][100], int i, int j, char c){ //������ ���
	visited[i][j]=1;
	for(int k=0; k<4; k++){
		int ni=i+vi[k];
		int nj=j+vj[k];
		if(0<=ni && ni<n && 0<=nj && nj<n){
			if(c=='R'){ //c�� R�� ��
				if((color[ni][nj]=='R'||color[ni][nj]=='G') && visited[ni][nj]==0) //������ ĭ�� R �Ǵ� G�� ���
					dfs_blind(color, visited, ni, nj, 'R'); //c�� R�� �Ͽ� dfs_blind ����
			}
			else{ //c�� B�� ��
				if(color[ni][nj]=='B' && visited[ni][nj]==0) //������ ĭ�� B�� ���
					dfs_blind(color, visited, ni, nj, 'B'); //c�� B�� �Ͽ� dfs_blind ����
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
			cin>>color[i][j]; //�� ���ھ� �Է¹ޱ�
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){ //������ �ƴ� ��쿡 ���� �湮���� ���� �� ã��
			if(color[i][j]=='R' && visited[i][j]==0){ //�������� R�� ��
				dfs_noblind(color, visited, i, j, 'R');
				noblindness++; //���� ����
			}
			if(color[i][j]=='G' && visited[i][j]==0){ //�������� G�� ��
				dfs_noblind(color, visited, i, j, 'G');
				noblindness++; //���� ����
			}
			if(color[i][j]=='B' && visited[i][j]==0){ //�������� B�� ��
				dfs_noblind(color, visited, i, j, 'B');
				noblindness++; //���� ����
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			visited[i][j]=0; //�湮��� �ʱ�ȭ
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){ //������ ��쿡 ���� �湮���� ���� �� ã��
			if((color[i][j]=='R' || color[i][j]=='G') && visited[i][j]==0){ //�������� R �Ǵ� G�� ��
				dfs_blind(color, visited, i, j, 'R'); //c�� R�� �Ͽ� dfs_noblind ȣ��
				blindness++; //���� ����
			}
			if(color[i][j]=='B' && visited[i][j]==0){ //�������� B�� ��
				dfs_blind(color, visited, i, j, 'B'); //c�� B�� �Ͽ� dfs_noblind ȣ��
				blindness++; //���� ����
			}
		}
	}

	cout<<noblindness<<" "<<blindness<<endl;
	return 0;
}
