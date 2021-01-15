/*RGB거리에 사는 사람들은 집을 빨강, 초록, 파랑중에 하나로 칠하려고 한다. 또한, 그들은 모든 이웃은 같은 색으로 칠할 수 없다는 규칙도 정했다. 집 i의 이웃은 집 i-1과 집 i+1이고, 첫 집과 마지막 집은 이웃이 아니다.

각 집을 빨강으로 칠할 때 드는 비용, 초록으로 칠할 때 드는 비용, 파랑으로 드는 비용이 주어질 때, 모든 집을 칠하는 비용의 최솟값을 구하는 프로그램을 작성하시오.
첫째 줄에 모든 집을 칠하는 비용의 최솟값을 출력한다.
 */
#include <iostream>
#include <algorithm>
using namespace std;

int D[10001][3];
int cost[10001][3];
int main(){
	int n;
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>cost[i][0]>>cost[i][1]>>cost[i][2];
	}
	for(int i=1; i<=n; i++){
		D[i][0]=min(D[i-1][1], D[i-1][2])+cost[i][0];
		D[i][1]=min(D[i-1][0], D[i-1][2])+cost[i][1];
		D[i][2]=min(D[i-1][0], D[i-1][1])+cost[i][2];
	}

	cout<<min(min(D[n][0], D[n][1]), D[n][2]);
	return 0;
}
//수행시간: O(n)
