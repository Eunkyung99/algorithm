#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M;
int board[50][50];
int dr[5] = {0, 0, 1, 0, -1};
int dc[5] = {0, -1, 0, 1, 0};
vector<pair<int, int> > v;
int exploded[4] = {0,};
vector<pair<int, int> > change;

void PutNumber(){
    int r = N/2;
    int c = N/2;
    int d = 1;
    int move = 1;

    while(1){
        for(int m=0; m<move; m++){
            r = r + dr[d];
            c = c + dc[d];
            v.push_back(make_pair(r, c));
        }
        if(v.size() == N*N){ //******** N*N-1하니까 무한루프
            v.pop_back(); //마지막에 쓰레기값 들어감!!!
            break;
        }
        if(d%2 == 0){ //방향 2, 4인 경우 이동칸 증가
            move += 1;
        }
        d = (d+1)%4;
        if(d==0){ d=4;} //******
    }
}

void ThrowIce(int d, int S){
    int sharkR = N/2;
    int sharkC = N/2;

    for(int s=1; s<=S; s++){
        int nr = sharkR + dr[d]*s;
        int nc = sharkC + dc[d]*s;
        if(0<=nr && nr<N && 0<=nc && nc<N){
            board[nr][nc] = 0;
        }
    }
}

void MoveMarble(){
    for(int i=0; i<v.size()-1; i++){
        pair<int, int> now = v[i];
        if(board[now.first][now.second] == 0){ //현재 칸이 비어있으면
            for(int nextD=i+1; nextD<v.size(); nextD++){ //다음 빈칸을 찾음 ********* 무조건 1칸씩 당기면 안 됐음 ****
                pair<int, int> next = v[nextD];
                if(board[next.first][next.second] != 0){
                    board[now.first][now.second] = board[next.first][next.second];
                    board[next.first][next.second] = 0;
                    break; //nextD 찾고 당겼으니 break
                }
            }
        }
    }
}

bool ExplodeMarble(){
    change.clear(); //초기화
    vector<pair<int, int> > tmp;
    int num = -1;
    bool hasExploded = false;

    for(int i=0; i<v.size(); i++){ //**** 0번부터 시작
        if(num == 0){ break; } //빈 칸 되면
        if(board[v[i].first][v[i].second] == num){ //연속되면
            tmp.push_back(make_pair(v[i].first, v[i].second));
        }else{ //수가 바뀌면
            if(tmp.size() >= 4){ //4개 이상 연속되었으면
                for(int t=0; t<tmp.size(); t++){
                    int r = tmp[t].first;
                    int c = tmp[t].second;
                    exploded[board[r][c]] += 1; //폭발된 구슬 개수 세기
                    board[r][c] = 0; //폭발시킴
                    hasExploded = true;
                }
            }else if(tmp.size() > 0){
                change.push_back(make_pair(tmp.size(), num)); //폭발되지 않은 경우 순서 유지됨
            }

            tmp.clear();
            num = board[v[i].first][v[i].second];
            tmp.push_back(make_pair(v[i].first, v[i].second));
        }
    }
    return hasExploded;
}

void ChangeMarble(){
    memset(board, 0, sizeof(board)); //**** 초기화
    for(int i=0; i<v.size(); i+=2){
        if(change.size() == 0){ //원소가 더 적을 수도 있었음 ********** segfault - 처음부터 검사해야 함!!!!
            break; 
        }
        board[v[i].first][v[i].second] = change[0].first;
        board[v[i+1].first][v[i+1].second] = change[0].second;
        change.erase(change.begin()+0);
    }
}

int main(){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
        }
    }

    PutNumber();
    
    int d, s;
    for(int i=0; i<M; i++){
        cin >> d >> s;
        //3->1, 2->2, 4->3, 1->4
        if(d==3){d=1;}
        else if(d==4){d=3;}
        else if(d==1){d=4;}
        ThrowIce(d, s);
        MoveMarble(); 

        while(1){
            bool hasExploded = ExplodeMarble();
            if(!hasExploded){ break; }
            MoveMarble();
        }
        
        ChangeMarble();
    }

    cout << exploded[1] + exploded[2]*2 + exploded[3]*3 <<"\n";

    return 0;
}