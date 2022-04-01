#include <iostream>
#include <vector>
using namespace std;

struct Shark{
    int d, s, z;
};

int kingC = 0;
int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, 1, -1};

int R, C, M;
vector<Shark> sea[101][101];

void Move(){
    vector<Shark> tmp[101][101];
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++){
            if(sea[i][j].size() > 0){
                Shark shark = sea[i][j][0];
                sea[i][j].pop_back();
                int nr = i;
                int nc = j;
                
                for(int a=0; a<shark.s; a++){ //속력만큼 이동 ******* 직접 반복문으로 계산 아이디어 부족!!!
                    nr += dr[shark.d];
                    nc += dc[shark.d];
                    if(nr<1){
                        nr += 2;
                        shark.d = 2; //아래 방향 
                    }else if(nr>R){
                        nr -= 2;
                        shark.d = 1; //위 방향
                    }else if(nc<1){
                        nc += 2;
                        shark.d = 3; //오른쪽 방향
                    }else if(nc>C){
                        nc -= 2;
                        shark.d = 4; //왼쪽 방향
                    }
                }
                //자리를 찾았으면 거기에 상어가 더 있는지 확인
                if(tmp[nr][nc].size() == 0){
                    tmp[nr][nc].push_back(shark);
                }else{ //상어가 이미 있으면 크기 비교
                    Shark existed = tmp[nr][nc][0];
                    tmp[nr][nc].pop_back();
                    if(existed.z > shark.z){
                        tmp[nr][nc].push_back(existed);
                    }else{
                        tmp[nr][nc].push_back(shark);
                    }
                }
            }
        }
    }
    for(int i=1; i<=R; i++){
        for(int j=1; j<=C; j++){
            if(tmp[i][j].size() > 0){
                sea[i][j].push_back(tmp[i][j][0]);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int ans = 0;
    int r, c, s, d, z;
    cin >> R >> C >> M;

    Shark shark;
    for(int m=0; m<M; m++){
        cin >> r >> c >> s >> d >> z;
        if(d==1 || d==2){
            shark.s = s % ((R-1)*2); //******
        }else{
            shark.s = s % ((C-1)*2);
        }
        shark.d = d;
        shark.z = z;
        sea[r][c].push_back(shark);
    }

    while(kingC < C){
        kingC++;
        int i=1;
        while(i<=R){
            if(sea[i][kingC].size() == 1){
                ans += sea[i][kingC][0].z;
                sea[i][kingC].erase(sea[i][kingC].begin());
                break;
            }
            i+=1;
        }
        Move();
    }
    
    cout << ans <<"\n";

    return 0;
}