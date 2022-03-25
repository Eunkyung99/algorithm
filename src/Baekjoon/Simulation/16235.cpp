#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct tree{
    int age;
    bool isLive;
};

// bool comp(const tree &a, const tree &b){
    // if(a.isLive && !b.isLive){
    //     return -1;
    // }else if(!a.isLive && b.isLive){
    //     return 1;
    // }else if(a.isLive && b.isLive){
    //     return a.age < b.age;
    // }
    // return 1;
// }

int dr[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dc[8] = {0, 0, -1, 1, 1, -1, 1, -1};

int N, M, K;

vector<tree> trees[11][11];
int garden[11][11]; //남아있는 양분
int A[11][11]; //겨울마다 추가되는 양분
int died[11][11]; //죽어서 추가될 양분

void S2D2(){
    // for(int i=1; i<=N; i++){
    //     for(int j=1; j<=N; j++){
    //         sort(trees[i][j].begin(), trees[i][j].end(), comp);
    //         died[i][j] = 0; //init
    //     }
    // }
    memset(died, 0, sizeof(died));

    //봄
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            for(int t=trees[i][j].size()-1; t>=0; t--){ //**************** 나이가 적은 애는 계속 맨 뒤에 추가되므로 정렬할 필요 없음!!!!
                if(trees[i][j][t].isLive == true){
                    if(trees[i][j][t].age > garden[i][j]){
                        trees[i][j][t].isLive = false; //죽음
                        died[i][j] += trees[i][j][t].age/2;
                    }else{
                        garden[i][j] -= trees[i][j][t].age;
                        trees[i][j][t].age += 1;
                    }
                }
            }
        }
    }

    //여름
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            garden[i][j] += died[i][j];
        }
    }

    //가을
    tree tr; //아기 나무
    tr.age = 1;
    tr.isLive = true;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            for(int t=trees[i][j].size()-1; t>=0; t--){ //***** size - 1  
                if(trees[i][j][t].isLive == false){
                    trees[i][j].erase(trees[i][j].begin(), trees[i][j].begin()+t); //죽은 애들 다 지워주기
                    break;
                }
                if(trees[i][j][t].isLive && (trees[i][j][t].age%5==0)){
                    for(int d=0; d<8; d++){
                        int nr = i + dr[d];
                        int nc = j + dc[d];
                        if(1<=nr && nr<=N && 1<=nc && nc<=N){
                            trees[nr][nc].push_back(tr);
                        }
                    }
                }
            }
        }
    }

    //겨울
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            garden[i][j] += A[i][j];
        }
    }
}

int main(){
    int x, y, z;
    tree tr;
    int ans = 0;

    cin >> N >> M >> K;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> A[i][j]; //추가되는 양분
            garden[i][j] = 5; //초기화
        }
    }
    
    for(int i=0; i<M; i++){
        cin >> x >> y >> z;
        tr.age = z;
        tr.isLive = true;
        trees[x][y].push_back(tr);
    }

     for(int k=0; k<K; k++){
         S2D2();
     }
     
     for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            for(int t=0; t<trees[i][j].size(); t++){
                if(trees[i][j][t].isLive){
                    ans += 1;
                }
            }
        }
     }

     cout << ans <<"\n";

    return 0;
}