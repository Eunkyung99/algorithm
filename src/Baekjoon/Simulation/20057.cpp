#include <iostream>
using namespace std;

int N;
int A[500][500];
int dr[4] = {0, 1, 0, -1};
int dc[4] = {-1, 0, 1, 0};
int ans = 0;

void Spread(int r, int c, int d, int n, int amount){
    for(int x=0; x<2; x++){
        d = (d+(x*2))%4; //d, d+2
        int nr = r + dr[d]*n;
        int nc = c + dc[d]*n;
        if(0<=nr && nr<N && 0<=nc && nc<N){
            A[nr][nc] += amount;
        }else{
            ans += amount;
        }
    }
}

void Tornado(){
    bool flag = true;
    int nr = N/2;
    int nc = N/2;
    int move = 1; //이동하는 개수
    int dir = 0;

    while(flag){
        for(int m=0; m<move; m++){
            nr += dr[dir];
            nc += dc[dir];
            if(!(0<=nr && nr<N && 0<=nc && nc<N)){ //************밖에서 검사하지 말고 안에서 검사해야 함!!!!!
                flag = false;
                break;
            }
            //r, c에서 nr, nc로 dir 방향으로 이동
            int y = A[nr][nc];
            int dust1 = y*1/100; //2개 ****************(1/100) 괄호 묶으면 안 됨!!
            int dust2 = y*2/100; //2개
            int dust5 = y*5/100; //1개
            int dust7 = y*7/100; //2개
            int dust10 = y*10/100; //2개
            int alpha = y - (dust1*2) - (dust2*2) - (dust5) - (dust7*2) - (dust10*2);

            A[nr][nc] = 0; //y 다 날아감

            //90도 꺾은 방향
            int d = (dir+1)%4;
    
            //반대 방향으로 한 칸 가서 90도 꺾은 경우 2개 - dust1
            int r = nr - dr[dir];
            int c = nc - dc[dir];
            Spread(r, c, d, 1, dust1);

            r += dr[dir];
            c += dc[dir];
            //nr, nc 기준 90도 꺾은 경우 2개*2 - dust7, dust2
            Spread(r, c, d, 1, dust7);
            Spread(r, c, d, 2, dust2);

            r += dr[dir];
            c += dc[dir];
            //alpha 기준 90도 꺾은 경우 2개 - dust10
            Spread(r, c, d, 1, dust10);
            
            //alpha
            if(0<=r && r<N && 0<=c && c<N){
                A[r][c] += alpha;
            }else{
                ans += alpha;
            }
            
            r += dr[dir];
            c += dc[dir];
            //dust5
            if(0<=r && r<N && 0<=c && c<N){
                A[r][c] += dust5;
            }else{
                ans += dust5;
            }
        }

        // if(!(0<=nr && nr<N && 0<=nc && nc<N)){
        //     break;
        // }
        if(dir%2==1){
            move += 1; //두 번 move할 때마다 move 증가
        }
        dir = (dir+1)%4;
    }

}
int main(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> A[i][j];
        }
    }

    Tornado();

    cout << ans <<"\n";

    return 0;
}