#include <iostream>
using namespace std;

int K;

int gear[5][8];
bool isRotate[4]; //1: 1-2 2: 2-3 3: 3-4

void checkWhatRotate(){
    for(int i=1; i<4; i++){
        int right = gear[i][2];
        int left = gear[i+1][6]; //***
        if(right != left){
            isRotate[i] = true;
        }else{
            isRotate[i] = false;
        }
    }
}

void Rotate(int n, int d){
    if((n > 1) && isRotate[n-1]){ //left
        isRotate[n-1] = false;
        Rotate(n-1, (-1)*d);
    }
    if((n < 4) && isRotate[n]){ //right
        isRotate[n] = false;
        Rotate(n+1, (-1)*d);
    }

    if(d == 1){
       int tmp = gear[n][7];
       for(int i=7; i>0; i--){
           gear[n][i] = gear[n][i-1];
       }
       gear[n][0] = tmp;
    }else if(d == -1){ //d == -1
        int tmp = gear[n][0];
        for(int i=0; i<7; i++){
            gear[n][i] = gear[n][i+1];
        }
        gear[n][7] = tmp;
    }
}

int getScore(){
    int score = 0;
    if(gear[1][0] == 1){
        score += 1;
    }
    if(gear[2][0] == 1){
        score += 2;
    }
    if(gear[3][0] == 1){
        score += 4;
    }
    if(gear[4][0] == 1){
        score += 8;
    }
    return score;
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int num, dir;
    string s;

    for(int i=1; i<=4; i++){
        cin >> s;
        for(int j=0; j<8; j++){
            gear[i][j] = s[j] - '0';
        }
    }
    cin >> K;
    for(int k=0; k<K; k++){
        cin >> num >> dir;
        checkWhatRotate();
        Rotate(num, dir);
    }

    cout << getScore() <<"\n";

    return 0;
}