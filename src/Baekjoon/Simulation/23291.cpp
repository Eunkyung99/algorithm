#include <iostream>
#include <vector>
using namespace std;

int N, K;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<vector<int> > fishBowl(101);

pair<int, int> MoveFish(int r, int c){
    int tmp[101][101];
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            tmp[i][j] = fishBowl[i][j];
        }
    }

    for(int i=0; i<c; i++){
        fishBowl[0].erase(fishBowl[0].begin());
    }

    for(int i=1; i<r; i++){
        fishBowl[i].clear();
    }
    
    //tmp 오른쪽으로 90도 회전시키기
    int nr = 1;
    for(int j=c-1; j>=0; j--){
        for(int i=0; i<r; i++){
            fishBowl[nr].push_back(tmp[i][j]);
        }
        nr += 1;
    }

    return make_pair(c+1, r); //현재 쌓인 층수
}

void Move(int r, int c){
    int tmp[101][101] = {0, };
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(fishBowl[i][j] > 0){
                for(int d=0; d<4; d++){
                    int nr = i + dr[d];
                    int nc = j + dc[d];
                    if(0<=nr && nr<r && 0<=nc && nc<c && fishBowl[i][j] < fishBowl[nr][nc]){ //**** N 오타!
                        int diff = (fishBowl[nr][nc] - fishBowl[i][j])/5;
                        if(diff > 0){
                            tmp[i][j] += diff;
                            tmp[nr][nc] -= diff;
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            fishBowl[i][j] += tmp[i][j];
        }
    }
}

int MakeOne(int r, int c){
    int maxFish = 0;
    int minFish = 999999;
    vector<int> newLine;
    for(int j=0; j<c; j++){
        for(int i=0; i<r; i++){
            if(fishBowl[i][j] > 0){
                newLine.push_back(fishBowl[i][j]);
                if(fishBowl[i][j] > maxFish){
                    maxFish = fishBowl[i][j];
                }
                if(fishBowl[i][j] < minFish){
                    minFish = fishBowl[i][j];
                }
            }
        }
    }
    
    for(int i=0; i<r; i++){
        fishBowl[i].clear();
    }

    for(int i=0; i<newLine.size(); i++){
        fishBowl[0].push_back(newLine[i]);
    }

    return maxFish - minFish;
}

void Above(int s){
    vector<int> tmp;
    vector<vector<int> > tmp2(2);

    for(int j=0; j<s/2; j++){
        tmp.push_back(fishBowl[0][0]); //******* 삭제 시 인덱스 주의
        fishBowl[0].erase(fishBowl[0].begin());
    }

    //0번째 줄 뒤집기
    for(int j=s/2-1; j>=0; j--){
        fishBowl[1].push_back(tmp[j]); //뒤에서부터 역순으로 뒤집기
    }

    //2번째 공중부양
    for(int j=s/4-1; j>=0; j--){
        tmp2[1].push_back(fishBowl[0][j]);
        tmp2[0].push_back(fishBowl[1][j]);
        fishBowl[0].erase(fishBowl[0].begin()+j);
        fishBowl[1].erase(fishBowl[1].begin()+j);
    }

    for(int j=0; j<s/4; j++){
        fishBowl[2].push_back(tmp2[0][j]);
        fishBowl[3].push_back(tmp2[1][j]);
    }

    // for(int j=s/4; j<s/2; j++){ //****** s/2까지 있음!!!
    //     fishBowl[2].push_back(fishBowl[0][s/4]);
    //     fishBowl[3].push_back(fishBowl[1][s/4]);
    //     fishBowl[0].erase(fishBowl[0].begin()+s/4);
    //     fishBowl[1].erase(fishBowl[1].begin()+s/4);
    // }

    // //(0, s/4) ~ (1, s/4) 뒤집기
    // for(int j=s/4-1; j>=0; j--){
    //     tmp2[0].push_back(fishBowl[1][j]);
    //     tmp2[1].push_back(fishBowl[0][j]);
    // }

    // for(int i=0; i<2; i++){
    //     for(int j=0; j<s/4; j++){
    //         fishBowl[i][j] = tmp2[i][j];
    //     }
    // }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int turn = 1;
    int fish;
    cin >> N >> K;
    for(int i=0; i<N; i++){
        cin >> fish; 
        fishBowl[0].push_back(fish); //바닥: N행
    }

    while(1){
        int minVal = 999999;
        vector<int> minV;

        for(int i=0; i<fishBowl[0].size(); i++){
            if(fishBowl[0][i] < minVal){
                minVal = fishBowl[0][i];
                minV.clear();
                minV.push_back(i);
            }else if(fishBowl[0][i] == minVal){
                minV.push_back(i);
            }
        }
        
        for(int i=0; i<minV.size(); i++){
            fishBowl[0][minV[i]] += 1; 
        }

        //공중부양
        pair<int, int> p; //(가로 개수, 세로 개수)
        p.first = 1;
        p.second = 1;
        while(1){
            p = MoveFish(p.first, p.second);
            if(fishBowl[0].size() - p.second < p.first){
                break;
            }
        }
        
       //빈 칸 채우기
        int s = fishBowl[0].size();
        for(int i=1; i<p.first; i++){
            int cnt = s-fishBowl[i].size(); //************** for문 안에 넣으면 안 됨!! 변하는 값!!!
            for(int put=1; put<=cnt; put++){
                fishBowl[i].push_back(0); //** 빈 칸 표시!
            }
        }

        Move(p.first, s);

        //한 줄 만들기 
        MakeOne(p.first, s);

        //공중부양
        s = fishBowl[0].size();
        Above(s);

        //물고기 조절
        Move(4, s/4);

        int res = MakeOne(4, s/4);

        if(res <= K){
            break;
        }

        turn += 1;
    }



    cout << turn << "\n";

    return 0;
}