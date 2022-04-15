#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N, M;
int water[51][51];
int dr[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dc[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
vector<pair<int, int> > cloud;
vector<pair<int, int> > v;
bool visited[51][51];

int main(){
    int ans = 0;
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> water[i][j];
        }
    }

    //(N, 1), (N, 2), (N-1, 1), (N-1, 2)에 구름 생성
    cloud.push_back(make_pair(N, 1));
    cloud.push_back(make_pair(N, 2));
    cloud.push_back(make_pair(N-1, 1));
    cloud.push_back(make_pair(N-1, 2));

    int d, s;
    for(int i=0; i<M; i++){
        memset(visited, false, sizeof(visited));
        cin >> d >> s;
        //전체 구름 이동
        for(int c=0; c<cloud.size(); c++){
            pair<int, int> p = cloud[c];
            int nr = (p.first + dr[d]*s)%N;
            int nc = (p.second + dc[d]*s)%N;
            if(nr<=0){ nr += N; }
            if(nc<=0){ nc += N; }
            water[nr][nc] += 1; //1-2단계(구름 이동, 비 내리기)
            v.push_back(make_pair(nr, nc)); //물복사버그 마법 실행 위치
            visited[nr][nc] = true; //3단계에서 사라질 구름 위치 표시 
        }

        cloud.clear(); //3단계

        for(int i=0; i<v.size(); i++){
            pair<int, int> p = v[i];
            int cnt = 0;
            for(int d=2; d<=8; d+=2){ //***********대각선 방향만 확인!!!
                int nr = p.first + dr[d];
                int nc = p.second + dc[d];
                if(1<=nr && nr<=N && 1<=nc && nc<=N){
                    if(water[nr][nc]>0){ cnt += 1; }
                }
            }
            water[p.first][p.second] += cnt;
        }
        v.clear();

        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                if(water[i][j] >= 2 && !visited[i][j]){
                    cloud.push_back(make_pair(i, j));
                    water[i][j] -= 2;
                }
            }
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            ans += water[i][j];
        }
    }

    cout << ans <<"\n";

    return 0;
}