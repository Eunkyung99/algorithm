#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<pair<int, int> > house;
vector<pair<int, int> > store;
int ans = 999999;

int calcDist(int flag){
    int sum = 0;
    for(int i=0; i<house.size(); i++){
        pair<int, int> h = house[i];
        int minDist = 9999; //최댓값으로 초기화 
        for(int j=0; j<store.size(); j++){
            //i번 집과 가장 가까운 치킨 집 찾기 - flag 켜져 있는 치킨 집만 검사
            if(flag & (1 << j)){
                int dist = abs(h.first - store[j].first) + abs(h.second - store[j].second);
                if(dist < minDist){
                    minDist = dist;
                }
            }
        }
        sum += minDist;
    }
    return sum;
}

void DFS(int visit, int m, int last){
    if(m == M){
        //치킨 거리 계산 (visit flag 사용)
        int res = calcDist(visit);
        if(res < ans){
            ans = res;
        }
        return;
    }

    for(int i=last+1; i<store.size(); i++){
        if( !((1 << i) & visit )){
            DFS((1<<i)+visit, m+1, i);
        }
    }
}

int main(){
    cin >> N >> M;

    int space;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> space;
            if(space == 1){
                house.push_back(make_pair(i, j));
            }else if(space == 2){
                store.push_back(make_pair(i, j));
            }
        }
    }

    DFS(0, 0, -1);
    
    cout << ans <<"\n";

    return 0;
}