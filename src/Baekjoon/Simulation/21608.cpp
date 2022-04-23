#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
int seat[21][21];
int idx[21][21];
int ans = 0;
int score[5] = {0, 1, 10, 100, 1000};

struct Student{
    int num;
    int like[4];
};

struct Seat{
    int r;
    int c;
    int empty;
    int likes;
};
vector<Student> v;

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

struct comp{
    bool operator()(const Seat& a, const Seat& b){
        if(a.likes == b.likes){
            if(a.empty == b.empty){
                if(a.r == b.r){
                    return a.c > b.c;
                }
                return a.r > b.r;
            }
            return a.empty < b.empty;
        }
        return a.likes < b.likes;
    }
};

int main(){
    Seat seatInfo;
    cin >> N;
    Student s;
    for(int i=0; i<N*N; i++){
        cin >> s.num >> s.like[0] >> s.like[1] >> s.like[2] >> s.like[3];
        v.push_back(s);
    }

    for(int i=0; i<N*N; i++){
        priority_queue<Seat, vector<Seat>, comp> pq;
        for(int r=1; r<=N; r++){
            for(int c=1; c<=N; c++){
                if(seat[r][c] == 0){ //빈 칸인 경우 후보
                    int empty = 0;
                    int likes = 0;
                    for(int d=0; d<4; d++){
                        int nr = r + dr[d];
                        int nc = c + dc[d];
                        if(1<=nr && nr<=N && 1<=nc && nc<=N){
                            if(seat[nr][nc] == 0){
                                empty += 1;
                            }else{
                                for(int l=0; l<4; l++){
                                    if(seat[nr][nc] == v[i].like[l]){
                                        likes += 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    seatInfo.r = r;
                    seatInfo.c = c; 
                    seatInfo.empty = empty;
                    seatInfo.likes = likes;
                    pq.push(seatInfo);
                }
            }
        }
        Seat seatTop = pq.top();
        seat[seatTop.r][seatTop.c] = v[i].num;
        idx[seatTop.r][seatTop.c] = i; //index 기록
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            int studentIdx = idx[i][j];
            int cnt = 0;
            for(int d=0; d<4; d++){
                int nr = i + dr[d];
                int nc = j + dc[d];
                if(1<=nr && nr<=N && 1<=nc && nc<=N){
                    for(int l=0; l<4; l++){
                        if(seat[nr][nc] == v[studentIdx].like[l]){
                            cnt += 1; 
                            break;
                        }
                    }
                }
            }
            ans += score[cnt];
        }
    }

    cout << ans << "\n";
    return 0;
}