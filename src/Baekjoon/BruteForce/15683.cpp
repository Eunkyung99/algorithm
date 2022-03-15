#include <iostream>
#include <vector>
using namespace std;

int N, M;
int office[9][9];
int dr[4] = { 0, -1, 0, 1 }; //left up right down
int dc[4] = { -1, 0, 1, 0 };

vector<pair<int, int> > v; //cctv
int answer = 9999;

void Bruteforce(int idx){
    if(idx == v.size()){
        //감시영역 세기
        int cnt = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(office[i][j] == 0){
                    cnt += 1;
                }
            }
        }
        answer = answer > cnt ? cnt : answer;
        return; //segfault error
    }

    int cctvR = v[idx].first;
    int cctvC = v[idx].second;

    if(office[cctvR][cctvC] == 1){
        for(int i=0; i<4; i++){
            int nr = cctvR;
            int nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[i];
                nc += dc[i];
            }
            Bruteforce(idx+1);
            //원상복구
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[i];
                nc += dc[i];
            }
        }
    }else if(office[cctvR][cctvC] == 2){
        for(int i=0; i<2; i++){
            int nr = cctvR;
            int nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[i];
                nc += dc[i];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[i+2];
                nc += dc[i+2];
            }
            Bruteforce(idx+1);
            //원상복구
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[i];
                nc += dc[i];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[i+2];
                nc += dc[i+2];
            }
        }
    }else if(office[cctvR][cctvC] == 3){
        for(int i=0; i<4; i++){
            int nr = cctvR;
            int nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[i];
                nc += dc[i];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[(i+1)%4];
                nc += dc[(i+1)%4];
            }
            Bruteforce(idx+1);
            //원상복구
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[i];
                nc += dc[i];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[(i+1)%4];
                nc += dc[(i+1)%4];
            }
        }
    }else if(office[cctvR][cctvC] == 4){
        for(int i=0; i<4; i++){
            int nr = cctvR;
            int nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[i];
                nc += dc[i];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[(i+1)%4];
                nc += dc[(i+1)%4];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[(i+2)%4];
                nc += dc[(i+2)%4];
            }
            Bruteforce(idx+1);
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[i];
                nc += dc[i];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[(i+1)%4];
                nc += dc[(i+1)%4];
            }
            nr = cctvR;
            nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == idx+9){
                    office[nr][nc] = 0;
                }
                nr += dr[(i+2)%4];
                nc += dc[(i+2)%4];
            }
        }
    }else{
        for(int i=0; i<4; i++){
            int nr = cctvR;
            int nc = cctvC;
            while((0<=nr && nr<N && 0<=nc && nc<M) && office[nr][nc]!=6){
                if(office[nr][nc] == 0){
                    office[nr][nc] = idx+9;
                }
                nr += dr[i];
                nc += dc[i];
            }
        }
        Bruteforce(idx+1);
    }
}



int main(){
    
    cin >> N >> M;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> office[i][j];
            if(office[i][j] > 0 && office[i][j] < 6){
                v.push_back(make_pair(i, j));
            }
        }
    }
    Bruteforce(0);
    cout << answer <<"\n";
    return 0;
}