#include <iostream>
using namespace std;

int N;
int board[21][21];

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int ans = 0;

void PushLeft(){
    for(int r=0; r<N; r++){
        for(int c=0; c<N; c++){
            if(board[r][c] > 0){ //움직인다
                int nr = r + dr[0];
                int nc = c + dc[0]; 
                while((0<=nr && nr<N && 0<=nc && nc<N) && board[nr][nc] == 0){
                    nr += dr[0];
                    nc += dc[0];
                }
                nr -= dr[0];
                nc -= dc[0];

                if(0<=nr && nr<N && 0<=nc && nc<N && board[nr][nc]==0){
                    board[nr][nc] = board[r][c];
                    board[r][c] = 0;
                }
            }
        }
    }
}

void PushRight(){
    for(int r=0; r<N; r++){
        for(int c=N-1; c>=0; c--){
            if(board[r][c] > 0){ //움직인다
                int nr = r + dr[1];
                int nc = c + dc[1]; 
                while((0<=nr && nr<N && 0<=nc && nc<N) && board[nr][nc] == 0){
                    nr += dr[1];
                    nc += dc[1];
                }
                nr -= dr[1];
                nc -= dc[1];

                if(0<=nr && nr<N && 0<=nc && nc<N && board[nr][nc]==0){
                    board[nr][nc] = board[r][c];
                    board[r][c] = 0;
                }
            }
        }
    }
}

void PushUp(){
    for(int c=0; c<N; c++){
        for(int r=0; r<N; r++){
            if(board[r][c] > 0){ //움직인다
                int nr = r + dr[2];
                int nc = c + dc[2]; 
                while((0<=nr && nr<N && 0<=nc && nc<N) && board[nr][nc] == 0){
                    nr += dr[2];
                    nc += dc[2];
                }
                nr -= dr[2];
                nc -= dc[2];

                if(0<=nr && nr<N && 0<=nc && nc<N && board[nr][nc]==0){
                    board[nr][nc] = board[r][c];
                    board[r][c] = 0;
                }
            }
        }
    }
}

void PushDown(){
    for(int c=0; c<N; c++){
        for(int r=N-1; r>=0; r--){
            if(board[r][c] > 0){ //움직인다
                int nr = r + dr[3];
                int nc = c + dc[3]; 
                while((0<=nr && nr<N && 0<=nc && nc<N) && board[nr][nc] == 0){
                    nr += dr[3];
                    nc += dc[3];
                }
                nr -= dr[3];
                nc -= dc[3];

                if(0<=nr && nr<N && 0<=nc && nc<N && board[nr][nc]==0){
                    board[nr][nc] = board[r][c];
                    board[r][c] = 0;
                }
            }
        }
    }
}

void CombineLeft(){
    for(int r=0; r<N; r++){
        for(int c=0; c<N-1; c++){
            if(board[r][c] > 0){
                if(board[r][c] == board[r][c+1]){
                    board[r][c] *= 2;
                    board[r][c+1] = 0;
                }
            }
        }
    }
}

void CombineRight(){
    for(int r=0; r<N; r++){
        for(int c=N-1; c>0; c--){
            if(board[r][c] > 0){
                if(board[r][c] == board[r][c-1]){
                    board[r][c] *= 2;
                    board[r][c-1] = 0;
                }
            }
        }
    }
}

void CombineUp(){
    for(int c=0; c<N; c++){
        for(int r=0; r<N-1; r++){
            if(board[r][c] > 0){
                if(board[r][c] == board[r+1][c]){
                    board[r][c] *= 2;
                    board[r+1][c] = 0;
                }
            }
        }
    }
}

void CombineDown(){
    for(int c=0; c<N; c++){
        for(int r=N-1; r>0; r--){
            if(board[r][c] > 0){
                if(board[r][c] == board[r-1][c]){
                    board[r][c] *= 2;
                    board[r-1][c] = 0;
                }
            }
        }
    }
}

void Copy(int orig[21][21], int copy[21][21]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            copy[i][j] = orig[i][j];
        }
    }
}
void DFS(int cnt){
    if(cnt == 5){
        int maxVal = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(maxVal < board[i][j]){
                    maxVal = board[i][j];
                }
            }
        }
        if(maxVal > ans){
            ans = maxVal;
        }
        return;
    }
    
    int tmp[21][21];
    Copy(board, tmp);
    for(int i=0; i<4; i++){
        if(i==0){
            PushLeft();
            CombineLeft();
            PushLeft();
        }else if(i==1){
            PushRight();
            CombineRight();
            PushRight();
        }else if(i==2){
            PushUp();
            CombineUp();
            PushUp();
        }else{
            PushDown();
            CombineDown();
            PushDown();
        }
        DFS(cnt+1);
        Copy(tmp, board); //원상복귀!!
    }
}
int main(){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
        }
    }
    
    DFS(0);
    
    cout << ans <<"\n";
    return 0;
}