#include <iostream>
#include <vector>
using namespace std;

int board[101][101] = {0,};
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

void DragonCurve(int r, int c, int d, int G){
    vector <int> v;
    int g = 0;
    int n = 1;
    board[r][c] = 1;
    int nr = r + dr[d];
    int nc = c + dc[d];
    board[nr][nc] = 1; //****** 0세데는 먼저 처리해줘야 함
    v.push_back((d+1)%4); 

    while(g < G){
        for(int i=n-1; i>=0; i--){
            int dir = v[i];
            nr += dr[dir];
            nc += dc[dir];
            board[nr][nc] = 1;
            v.push_back((dir+1)%4); //다음 방향 삽입
        }
        g = g+1;
        n = n*2;
    }
}

int main(){
    int N; 
    int answer = 0;
    cin >> N; 
    int x, y, d, g;
    for(int i=0; i<N; i++){
        cin >> x >> y >> d >> g;
        DragonCurve(y, x, d, g);
    }

    for(int i=0; i<100; i++){ //********** 범위는 (100, 100) 까지임
        for(int j=0; j<100; j++){
            if(board[i][j] && board[i][j+1] && board[i+1][j] && board[i+1][j+1]){
                answer += 1;
            }
        }
    }
    cout << answer <<"\n";
    return 0;
}