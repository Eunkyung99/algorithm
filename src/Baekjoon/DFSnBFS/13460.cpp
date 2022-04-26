#include <iostream>
using namespace std;

int N, M;
int board[11][11];

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int ans = 11;

int MoveLeft(){
    int res = 0;
    for(int i=1; i<N-1; i++){
        for(int j=1; j<M-1; j++){
            if(board[i][j] > 1){
                int nr = i + dr[0];
                int nc = j + dc[0];
                while((0<=nr && nr<N && 0<=nc && nc<M)){
                    if(board[nr][nc] == 0){
                        nr += dr[0];
                        nc += dc[0];
                    }else if(board[nr][nc] == -1){
                        if(board[i][j] == 2 && res==0){
                            board[i][j] = 0; //****** 자리 비우기
                            res = 1;
                        }else{
                            res = -1;
                        }
                        break;
                    }else{
                        break;
                    }
                }
                nr -= dr[0];
                nc -= dc[0];
                if((0<=nr && nr<N && 0<=nc && nc<M) && board[nr][nc] == 0){
                    board[nr][nc] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
    return res;
}

int MoveRight(){
    int res = 0;
    for(int i=1; i<N-1; i++){
        for(int j=M-2; j>0; j--){
            if(board[i][j] > 1){
                int nr = i + dr[1];
                int nc = j + dc[1];
                while((0<=nr && nr<N && 0<=nc && nc<M)){
                    if(board[nr][nc] == 0){
                        nr += dr[1];
                        nc += dc[1];
                    }else if(board[nr][nc] == -1){
                        if(board[i][j] == 2 && res==0){
                            board[i][j] = 0; //****** 자리 비우기
                            res = 1;
                        }else{
                            res = -1;
                        }
                        break;
                    }else{
                        break;
                    }
                }
                nr -= dr[1];
                nc -= dc[1];
                if((0<=nr && nr<N && 0<=nc && nc<M) && board[nr][nc] == 0){
                    board[nr][nc] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
    return res;
}

int MoveUp(){
    int res = 0;
    for(int j=1; j<M-1; j++){
        for(int i=1; i<N-1; i++){
            if(board[i][j] > 1){
                int nr = i + dr[2];
                int nc = j + dc[2];
                while((0<=nr && nr<N && 0<=nc && nc<M)){
                    if(board[nr][nc] == 0){
                        nr += dr[2];
                        nc += dc[2];
                    }else if(board[nr][nc] == -1){
                        if(board[i][j] == 2 && res==0){
                            board[i][j] = 0; //****** 자리 비우기
                            res = 1;
                        }else{
                            res = -1;
                        }
                        break;
                    }else{
                        break;
                    }
                }
                nr -= dr[2];
                nc -= dc[2];
                if((0<=nr && nr<N && 0<=nc && nc<M) && board[nr][nc] == 0){
                    board[nr][nc] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
    return res;
}

int MoveDown(){
    int res = 0;
    for(int j=1; j<M-1; j++){
        for(int i=N-2; i>0; i--){
            if(board[i][j] > 1){
                int nr = i + dr[3];
                int nc = j + dc[3];
                while((0<=nr && nr<N && 0<=nc && nc<M)){
                    if(board[nr][nc] == 0){
                        nr += dr[3];
                        nc += dc[3];
                    }else if(board[nr][nc] == -1){
                        if(board[i][j] == 2 && res==0){
                            board[i][j] = 0; //****** 자리 비우기
                            res = 1;
                        }else{
                            res = -1;
                        }
                        break;
                    }else{
                        break;
                    }
                }
                nr -= dr[3];
                nc -= dc[3];
                if((0<=nr && nr<N && 0<=nc && nc<M) && board[nr][nc] == 0){
                    board[nr][nc] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
    }
    return res;
}

void Copy(int orig[11][11], int copy[11][11]){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            copy[i][j] = orig[i][j];
        }
    }
}

void DFS(int cnt, int res){
    if(cnt > 10){
        return;
    }
    if(res == 1){ //success *********** 아래 for문에서 검사 시 리턴해버림
        if(ans > cnt){
            ans = cnt;
        }
        return;
    }else if(res == -1){ //fail
        return;
    }
    int tmp[11][11];
    Copy(board, tmp);

    for(int i=0; i<4; i++){
        int res;
        if(i==0){
            res = MoveLeft();
        }else if(i==1){
            res = MoveRight();
        }else if(i==2){
            res = MoveUp();
        }else{
            res = MoveDown();
        }
        DFS(cnt+1, res);
        Copy(tmp, board); //원상복귀
    } 
}

int main(){
    cin >> N >> M;
    string s;
    for(int i=0; i<N; i++){
        cin >> s;
        for(int j=0; j<M; j++){ //********* M끼지 주의!!
            if(s[j] == '.'){
                board[i][j] = 0;
            }else if(s[j] == '#'){
                board[i][j] = 1;
            }else if(s[j] == 'O'){
                board[i][j] = -1;
            }else if(s[j] == 'R'){
                board[i][j] = 2;
            }else{
                board[i][j] = 3;
            }
        }
    }

    DFS(0, 0);

    if(ans == 11){ ans = -1; }
    cout << ans <<"\n";
}