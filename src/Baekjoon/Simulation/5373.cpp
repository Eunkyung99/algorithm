#include <iostream>
using namespace std;

int T, N;
//****** 단순 구현 문제 - 전개도 그리기!!!
//****** 시계 방향 == 반시계 방향*3번
//0:윗면 1:앞면 2:아랫면 3:뒷면 4:왼쪽면 5:오른쪽면
char cube[6][3][3];

void CubeInit(){
    for(int r=0; r<3; r++){
        for(int c=0; c<3; c++){
            cube[0][r][c] = 'w';
            cube[1][r][c] = 'r';
            cube[2][r][c] = 'y';
            cube[3][r][c] = 'o';
            cube[4][r][c] = 'g';
            cube[5][r][c] = 'b';
        }
    }
}

//면 회전
void Rotate(int side, int dir){ //dir:0-시계
    char tmp[6][3][3];
    if(dir == 0){ //시계 방향
        int nc = 2;
        for(int r=0; r<3; r++){
            for(int c=0; c<3; c++){
                tmp[side][c][nc] = cube[side][r][c];
            }
            nc -= 1;
        }
    }else{
        int nc = 0;
        for(int r=0; r<3; r++){
            int nr = 0;
            for(int c=2; c>=0; c--){
                tmp[side][nr++][nc] = cube[side][r][c];
            }
            nc+=1;
        }
    }

    for(int r=0; r<3; r++){
        for(int c=0; c<3; c++){
            cube[side][r][c] = tmp[side][r][c];
        }
    }
}

//옆면 돌리기
void RotateUp(){ //윗면 시계 방향 돌리기 
    char tmp[3];

    for(int i=0; i<3; i++){
        tmp[i] = cube[3][2][i];
    }

    for(int i=0; i<3; i++){
        cube[3][2][i] = cube[4][2-i][2];
    }

    for(int i=0; i<3; i++){
        cube[4][2-i][2] = cube[1][0][2-i];
    }

    for(int i=0; i<3; i++){
        cube[1][0][2-i] = cube[5][i][0];
    }

    for(int i=0; i<3; i++){
        cube[5][i][0] = tmp[i];
    }
}

void RotateDown(){
    char tmp[3];

    for(int i=0; i<3; i++){
        tmp[i] = cube[1][2][i];
    }

    for(int i=0; i<3; i++){
        cube[1][2][i] = cube[4][i][0];
    }

    for(int i=0; i<3; i++){
        cube[4][i][0] = cube[3][0][2-i];
    }

    for(int i=0; i<3; i++){
        cube[3][0][2-i] = cube[5][2-i][2];
    }

    for(int i=0; i<3; i++){
        cube[5][2-i][2] = tmp[i];
    }
}

void RotateFront(){
    char tmp[3];

    for(int i=0; i<3; i++){
        tmp[i] = cube[0][2][i];
    }

    for(int i=0; i<3; i++){
        cube[0][2][i] = cube[4][2][i];
    }

    for(int i=0; i<3; i++){
        cube[4][2][i] = cube[2][0][2-i];
    }

    for(int i=0; i<3; i++){
        cube[2][0][2-i] = cube[5][2][i];
    }

    for(int i=0; i<3; i++){
        cube[5][2][i] = tmp[i];
    }
}

void RotateBack(){
    char tmp[3];

    for(int i=0; i<3; i++){
        tmp[i] = cube[2][2][i];
    }

    for(int i=0; i<3; i++){
        cube[2][2][i] = cube[4][0][2-i];
    }

    for(int i=0; i<3; i++){
        cube[4][0][2-i] = cube[0][0][2-i];
    }

    for(int i=0; i<3; i++){
        cube[0][0][2-i] = cube[5][0][2-i];
    }

    for(int i=0; i<3; i++){
        cube[5][0][2-i] = tmp[i];
    }
}

void RotateLeft(){
    char tmp[3];
    
    for(int i=0; i<3; i++){
        tmp[i] = cube[3][i][0];
    }

    for(int i=0; i<3; i++){
        cube[3][i][0] = cube[2][i][0];
    }

    for(int i=0; i<3; i++){
        cube[2][i][0] = cube[1][i][0];
    }

    for(int i=0; i<3; i++){
        cube[1][i][0] = cube[0][i][0];
    }

    for(int i=0; i<3; i++){
        cube[0][i][0] = tmp[i];
    }
}

void RotateRight(){
    char tmp[3];

    for(int i=0; i<3; i++){
        tmp[i] = cube[3][2-i][2];
    }

    for(int i=0; i<3; i++){
        cube[3][2-i][2] = cube[0][2-i][2];
    }

    for(int i=0; i<3; i++){
        cube[0][2-i][2] = cube[1][2-i][2];
    }

    for(int i=0; i<3; i++){
        cube[1][2-i][2] = cube[2][2-i][2];
    }

    for(int i=0; i<3; i++){
        cube[2][2-i][2] = tmp[i];
    }

}

int main(){
    char c, d;
    int side, dir;
    cin >> T;
    for(int i=1; i<=T; i++){
        CubeInit();
        cin >> N;
        for(int n=0; n<N; n++){
            cin >> c >> d;
            if(c=='U'){ side = 0; }
            else if(c=='F'){ side = 1; }
            else if(c=='D'){ side = 2; }
            else if(c=='B'){ side = 3; }
            else if(c=='L'){ side = 4; }
            else{ side = 5; }

            if(d=='+'){ dir = 0; }
            else{ dir = 1; }

            Rotate(side, dir);

            if(side==0){
                RotateUp();
                if(dir == 1){
                    RotateUp();
                    RotateUp();
                }
            }else if(side==1){
                RotateFront();
                if(dir == 1){
                    RotateFront();
                    RotateFront();
                }
            }else if(side==2){
                RotateDown();
                if(dir == 1){
                    RotateDown();
                    RotateDown();
                }
            }else if(side==3){
                RotateBack();
                if(dir == 1){
                    RotateBack();
                    RotateBack();
                }
            }else if(side==4){
                RotateLeft();
                if(dir == 1){
                    RotateLeft();
                    RotateLeft();
                }
            }else{
                RotateRight();
                if(dir == 1){
                    RotateRight();
                    RotateRight();
                }
            }
        }
        for(int r=0; r<3; r++){
            for(int c=0; c<3; c++){
                cout << cube[0][r][c];
            }
            cout <<"\n";
        }
    }

    return 0;
}