#include <iostream>
#include <vector>
using namespace std;

int N, K;
int board[13][13];
int dr[5] = {0, 0, 0, -1, 1};
int dc[5] = {0, 1, -1, 0, 0};

struct horse{
    int r;
    int c;
    int dir;
    int idx;
};

horse H[11];
vector<int> chess[13][13];

int White(int idx, int r, int c, int nr, int nc){
    for(int i=idx; i<chess[r][c].size(); i++){
        int num = chess[r][c][i];
        chess[nr][nc].push_back(num);
        if(chess[nr][nc].size() >= 4){
            return -1;
        }
        H[num].r = nr;
        H[num].c = nc;
        H[num].idx = chess[nr][nc].size() - 1;
    }
    for(int i=chess[r][c].size()-1; i>=idx; i--){
        chess[r][c].erase(chess[r][c].begin()+i);
    }
    return 0;
}
int Red(int idx, int r, int c, int nr, int nc){
    for(int i=chess[r][c].size()-1; i>=idx; i--){
        int num = chess[r][c][i];
        chess[nr][nc].push_back(num);
        if(chess[nr][nc].size() >= 4){
            return -1;
        }
        H[num].r = nr;
        H[num].c = nc;
        H[num].idx = chess[nr][nc].size() - 1;
        chess[r][c].erase(chess[r][c].begin()+i);
    }
    return 0;
}

int Move(int n){
    int r = H[n].r;
    int c = H[n].c;
    int d = H[n].dir;
    int idx = H[n].idx;

    int nr = r + dr[d];
    int nc = c + dc[d];

    int ret = 0;

    if(0<nr && nr<=N && 0<nc && nc<=N){
        if(board[nr][nc] == 0){ //white
            ret = White(idx, r, c, nr, nc);
        }else if(board[nr][nc] == 1){ //red
            ret = Red(idx, r, c, nr, nc);
        }else{ //blue
            if(d==1 || d==3){
                d = d + 1;
            }else{
                d = d - 1;
            }
            H[n].dir = d; //방향 바꾼거 기록
            nr = r + dr[d];
            nc = c + dc[d];
            if(0<nr && nr<=N && 0<nc && nc<=N){ //*********** 방향 바꾼 뒤에도 맵 범위 검사 필요!!!!!
                if(board[nr][nc] == 0){
                    ret = White(idx, r, c, nr, nc);
                }else if(board[nr][nc] == 1){
                    ret = Red(idx, r, c, nr, nc);
                }
            }
        }
    }else{
        if(d==1 || d==3){
            d = d + 1;
        }else{
            d = d - 1;
        }
        H[n].dir = d; //방향 바꾼거 기록
        nr = r + dr[d];
        nc = c + dc[d];
        if(0<nr && nr<=N && 0<nc && nc<=N){ //*********** 방향 바꾼 뒤에도 맵 범위 검사 필요!!!!!
            if(board[nr][nc] == 0){
                ret = White(idx, r, c, nr, nc);
            }else if(board[nr][nc] == 1){
                ret = Red(idx, r, c, nr, nc);
            }
        }
    }
    return ret;
}
int main(){
    int turn = 1;
    cin >> N >> K;
    for(int i=1; i<=N; i++){ //********* 칸 밀려서 오답 발생..
        for(int j=1; j<=N; j++){
            cin >> board[i][j];
        }
    }

    int r, c, d;
    for(int i=1; i<=K; i++){
        cin >> r >> c >> d;
        H[i].r = r;
        H[i].c = c;
        H[i].dir = d;
        H[i].idx = 0;
        chess[r][c].push_back(i);
    }

    int ret = 0;

    while(turn <= 1000){
        for(int i=1; i<=K; i++){
            ret = Move(i);
            if(ret == -1){
                break;
            }
        }
        if(ret == -1){
            break;
        }
        turn += 1;
    }
    
    if(turn == 1001){
        cout << "-1\n";
    }else{
        cout << turn <<"\n";
    }

    return 0;
}