/*
<그림 1>과 같이 정사각형 모양의 지도가 있다. 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다.
철수는 이 지도를 가지고 연결된 집들의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다.
여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 대각선상에 집이 있는 경우는 연결된 것이 아니다.
<그림 2>는 <그림 1>을 단지별로 번호를 붙인 것이다. 지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.
첫 번째 줄에는 총 단지수를 출력하시오. 그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.
*/
#include <iostream>
#include <algorithm>
using namespace std;

void dfs(int i, int j, int map[][27], int group[], int count){ //깊이 우선 탐색
	int vi[4]={0, 0, -1, 1}; //위 아래
	int vj[4]={-1, 1, 0, 0}; //좌 우
	group[count]+=1; //집의 수 증가
	map[i][j]=0; //방문 표시
	for(int k=0; k<4; k++){ //상하좌우 검사
		if(map[i+vi[k]][j+vj[k]]==1){ //집이 존재하며 방문하지 않은 경우
			dfs(i+vi[k], j+vj[k], map, group, count); //재귀
		}
	}
}
int main(){
	int n, count=0;
	int group[100000]={0,};
	int map[27][27]={0,};
	cin>>n;
	for(int i=1; i<n+1; i++){
		for(int j=1; j<n+1; j++)
			scanf("%1d", &map[i][j]); //숫자 하나씩 입력받기
	}
	for(int i=1; i<n+1; i++){
		for(int j=1; j<n+1; j++){
			if(map[i][j]==1){ //1이면
				dfs(i, j, map, group, count); //count번째 단지의 집 수 세기
				count++; //count 수 증가
			}
		}
	}
	cout<<count<<endl; //count=단지 수
	sort(group, group+count);//오름차순 정렬
	for(int i=0; i<count; i++){
		cout<<group[i]<<endl; //집 수 출력
	}
	return 0;
}
//수행시간: O(n^2)
