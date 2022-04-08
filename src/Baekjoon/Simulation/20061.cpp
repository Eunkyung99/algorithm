#include <iostream>
using namespace std;

int N;
int blue[4][6] = {0,};
int green[6][4] = {0,};
int score = 0;
int total = 0;

void Put(int t, int r, int c){
    if(t==1){
        //blue - r
        for(int j=0; j<5; j++){
            if(blue[r][j+1]){
                blue[r][j] = 1;
                break;
            }
            if(j==4){
                blue[r][5] = 1;
            }
        }

        //green - c
        for(int i=0; i<5; i++){
            if(green[i+1][c]){
                green[i][c] = 1;
                break;
            }
            if(i==4){
                green[5][c] = 1;
            }
        }
    }else if(t==2){
        //blue - r
        for(int j=0; j<4; j++){
            if(blue[r][j+2]){
                blue[r][j] = 1;
                blue[r][j+1] = 1;
                break;
            }
            if(j==3){
                blue[r][4] = 1;
                blue[r][5] = 1;
            }
        }

        //green - c
        for(int i=0; i<5; i++){
            if(green[i+1][c] || green[i+1][c+1]){
                green[i][c] = 1;
                green[i][c+1] = 1;
                break;
            }
            if(i==4){
                green[5][c] = 1;
                green[5][c+1] = 1;
            }
        }
    }else{
        //blue - r
        for(int j=0; j<5; j++){
            if(blue[r][j+1] || blue[r+1][j+1]){
                blue[r][j] = 1;
                blue[r+1][j] = 1;
                break;
            }
            if(j==4){
                blue[r][5] = 1;
                blue[r+1][5] = 1;
            }
        }
        //green - c
        for(int i=0; i<4; i++){
            if(green[i+2][c]){
                green[i][c] = 1;
                green[i+1][c] = 1;
                break;
            }
            if(i==3){
                green[4][c] = 1;
                green[5][c] = 1;
            }
        }
    }
}

void Check(){
    for(int i=0; i<6; i++){
        int cnt = 0;
        for(int j=0; j<4; j++){
            if(green[i][j] == 1){
                cnt += 1;
            }
        }
        if(cnt == 4){
            for(int r=i; r>0; r--){
                for(int c=0; c<4; c++){
                    green[r][c] = green[r-1][c];
                }
            }
            for(int x=0; x<4; x++){
                green[0][x] = 0;
            }
            score += 1;
        }
    }

    for(int j=0; j<6; j++){
        int cnt = 0;
        for(int i=0; i<4; i++){
            if(blue[i][j] == 1){
                cnt += 1;
            }
        }
        if(cnt == 4){
            for(int c=j; c>0; c--){
                for(int r=0; r<4; r++){
                    blue[r][c] = blue[r][c-1];
                }
            }
            for(int x=0; x<4; x++){
                blue[x][0] = 0;
            }
            score += 1;
        }
    }
}

void Special(){
    int special = 0;

    if(blue[0][0] || blue[1][0] || blue[2][0] || blue[3][0]){
        special += 1;
    }
    if(blue[0][1] || blue[1][1] || blue[2][1] || blue[3][1]){
        special += 1;
    }

    for(int s=0; s<special; s++){
        for(int c=5; c>0; c--){
            for(int r=0; r<4; r++){
                blue[r][c] = blue[r][c-1];
            }
        }
        for(int r=0; r<4; r++){
            blue[r][0] = 0;
        }
    }

    special = 0;
    if(green[0][0] || green[0][1] || green[0][2] || green[0][3]){
        special += 1;
    }
    if(green[1][0] || green[1][1] || green[1][2] || green[1][3]){
        special += 1;
    }

    for(int s=0; s<special; s++){
        for(int r=5; r>0; r--){
            for(int c=0; c<4; c++){
                green[r][c] = green[r-1][c];
            }
        }
        for(int c=0; c<4; c++){
            green[0][c] = 0;
        }
    }
}
int main(){
    int t, x, y;
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> t >> x >> y;
        Put(t, x, y);
        Check();
        Special();
    }

    for(int r=0; r<4; r++){
        for(int c=0; c<6; c++){
            if(blue[r][c]){
                total += 1;
            }
        }
    }

    for(int r=0; r<6; r++){
        for(int c=0; c<4; c++){
            if(green[r][c]){
                total += 1;
            }
        }
    }

    cout << score << "\n";
    cout << total << "\n";
    return 0;
}