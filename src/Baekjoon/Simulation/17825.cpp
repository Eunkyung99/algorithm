#include <iostream>
#include <cstring>
using namespace std;
int board[4][30] = {
    {-1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, 0, 0, 0, 0, 0, 0, 0},
    {-1, 2, 4, 6, 8, 10, 13, 16, 19, 25, 30, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {-1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 25, 30, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {-1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 28, 27, 26, 25, 30, 35, 40, 0, 0, 0, 0, 0, 0}
};
int dice[10];
int ans = 0;

struct Horse{
    int r;
    int c;
};
Horse h[4];
int record[4][30];

void DFS(int turn, int score, string route){
    if(turn == 10){
        if(score > ans){
            ans = score;
        }
        return;
    }

    for(int i=0; i<4; i++){ //말 4개를 모두 움직여 본다.
        int origR = h[i].r;
        int origC = h[i].c;
        int nextR = h[i].r;
        int nextC = origC + dice[turn];

        if(board[origR][origC] == 0){ continue; } //이미 도착했을 경우 말 이동하지 않음

        if(board[origR][nextC] == 10 && nextC == 5){ 
            nextR = 1; //1번 루트로
        }else if(board[origR][nextC] == 20 && nextC == 10){
            nextR = 2; //2번 루트로
        }else if(board[origR][nextC] == 30 && nextC == 15){ //********** 30 여러 개 존재
            nextR = 3; //3번 루트로
        }
        if(board[nextR][nextC] == 25){
            if(record[1][9]!=-1 || record[2][13]!=-1 || record[3][19]!=-1){
                continue;
            }
        }else if(board[nextR][nextC] == 30){
            if(nextC == 15){ //******************* 30이 여러 군데 있음!!!!
                if(record[nextR][nextC] != -1){
                    continue;
                }
            }else{
                if(record[1][10]!=-1 || record[2][14]!=-1 || record[3][20]!=-1){
                    continue;
                }
            }
        }else if(board[nextR][nextC] == 35){
            if(record[1][11]!=-1 || record[2][15]!=-1 || record[3][21]!=-1){
                continue;
            }
        }else if(board[nextR][nextC] == 40){
            if(record[0][20]!=-1 || record[1][12]!=-1 || record[2][16]!=-1 || record[3][22]!=-1){
                continue;
            }
        }else if(board[nextR][nextC] > 0 && record[nextR][nextC] != -1){ //말이 도착 칸을 넘어서지 않았는데 이미 말이 있을 경우
            // h[i].r = origR; //*********** 원상복귀해줘야 함!!!
            // h[i].c = origC;
            continue; //말을 이동할 수 없음
        }
        
        h[i].r = nextR;
        h[i].c = nextC;
        record[origR][origC] = -1; //*÷****************
        record[nextR][nextC] = i;
        DFS(turn+1, score + board[nextR][nextC], route+to_string(i));
        //원상복귀 -> 다음 말 돌 수 있음
        record[origR][origC] = i; //******** 원래 자리에 다시 표시
        record[nextR][nextC] = -1; //*******
        h[i].r = origR;
        h[i].c = origC;
        
    }
}

int main(){
    memset(record, -1, sizeof(record));
    for(int i=0; i<10; i++){
        cin >> dice[i];
    }
    for(int i=0; i<4; i++){
        h[i].r = 0; //기본 루트
        h[i].c = 0; //******
    }

    DFS(0, 0, "");

    cout << ans <<"\n";

    return 0;
}