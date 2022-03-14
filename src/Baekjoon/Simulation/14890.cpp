#include <iostream>
using namespace std;

int N, L;
int road[101][101];

int ans = 0;

int findRow(){
    int answer = 0;
    for(int i=0; i<N; i++){ 
        bool canBeAnswer = true;
        bool flag = false; //감소 체크해야 하는지 저장하는 flag
        int lastJ = 0;

        for(int j=0; j+1<N; j++){
            if(road[i][j] == road[i][j+1]){
                if(flag && (j+1 - lastJ + 1 == L)){
                    lastJ = j+2;
                    flag = false;
                }
            }else if(road[i][j] + 1 == road[i][j+1]){ //증가
                //lastJ ~ j까지 경사로를 놓아야 함
                if(flag){ //감소하는 거 처리가 안 된 경우
                    canBeAnswer = false;
                    break;
                }
                if(j - lastJ + 1 >= L){
                    lastJ = j+1; 
                }else{ //경사로를 놓을 수 없는 경우
                    canBeAnswer = false;
                    break;
                }
            }else if(road[i][j] - 1 == road[i][j+1]){ //감소 2 3 3 3 2 2 2
                if(flag){ //감소하는거 처리가 안 된 경우
                    canBeAnswer = false;
                    break;
                }
                if(L > 1){ //******
                    lastJ = j+1;
                    flag = true;
                }else{ //*********** L이 1인 경우는 플래그 처리 필요 없이 j+1에 경사로 놓았다고 가정!!!
                    lastJ = j+2;
                }
            }else{ //차이가 2 이상 나면 불가능
                canBeAnswer = false;
                break;
            }
        }

        if(!flag && canBeAnswer){
            answer++;
        }
    }
    return answer;
}

int findCol(){
    int answer = 0;
    for(int j=0; j<N; j++){ 
        bool canBeAnswer = true;
        bool flag = false;
        int lastI = 0;

        for(int i=0; i+1<N; i++){
            if(road[i][j] == road[i+1][j]){
                if(flag && (i+1 - lastI + 1 == L)){
                    lastI = i+2;
                    flag = false;
                }
            }else if(road[i][j] + 1 == road[i+1][j]){ 
                if(flag){ 
                    canBeAnswer = false;
                    break;
                }
                if(i - lastI + 1 >= L){
                    lastI = i+1; 
                }else{ 
                    canBeAnswer = false;
                    break;
                }
            }else if(road[i][j] - 1 == road[i+1][j]){ 
                if(flag){ 
                    canBeAnswer = false;
                    break;
                }
                if(L > 1){ 
                    lastI = i+1;
                    flag = true;
                }else{ 
                    lastI = i+2;
                }
            }else{ 
                canBeAnswer = false;
                break;
            }
        }

        if(!flag && canBeAnswer){
            answer++;
        }
    }
    return answer;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> road[i][j];
        }
    }

    cout << findRow() + findCol() <<"\n";

    return 0;
}