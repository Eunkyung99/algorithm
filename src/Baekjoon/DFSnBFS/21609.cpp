#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
int board[21][21];
int visited[21][21];
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

struct Block{
    int r;
    int c;
};

struct Group{
    int blocks;
    int rainbow;
    int baseR;
    int baseC;
    vector<Block> v;
};

struct compareGroup{
    bool operator()(const Group& a, const Group& b){
        if(a.blocks == b.blocks){
            if(a.rainbow == b.rainbow){
                if(a.baseR == b.baseR){
                    return a.baseC < b.baseC;
                }
                return a.baseR < b.baseR;
            }
            return a.rainbow < b.rainbow;
        }
        return a.blocks < b.blocks;
    }
};

struct compareBlock{
    bool operator()(const Block& a, const Block& b){
        if(a.r == b.r){
            return a.c > b.c;
        }
        return a.r > b.r;
    }
};

Group eraseG; // 제거해야 할 그룹

bool FindGroup(){
    memset(visited, -1, sizeof(visited));
    priority_queue<Group, vector<Group>, compareGroup> pqG;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(visited[i][j]==-1 && board[i][j]>0){ //무지개 블록을 제외한 기준점 찾기
                priority_queue<Block, vector<Block>, compareBlock> pqB; //기준점 블록
                queue<Block> q;
                Block block;
                Group group; //init
                group.blocks = 1; //********** 처음 들어간 블록 처리해줘야 했음
                group.rainbow = 0;
                int num = board[i][j]; //그룹에는 0 또는 num만 들어갈 수 있음

                visited[i][j] = num; //***************** 무지개는 다른 그룹이 다시 방문가능해야 했음 -> bool이 아닌 번호로 표기
                block.r = i;
                block.c = j;
                q.push(block);
                pqB.push(block); //******* 처음 들어간 블록 처리
                group.v.push_back(block); //*** 처음 들어간 블록 처리

                while(!q.empty()){
                    Block b = q.front();
                    q.pop();
                    for(int d=0; d<4; d++){
                        int nr = b.r + dr[d];
                        int nc = b.c + dc[d];
                        if((1<=nr && nr<=N && 1<=nc && nc<=N) && (board[nr][nc]==0 || board[nr][nc]==num) && visited[nr][nc]!=num){ //********visited 검사!!!! - 무한루프..
                            Block nb;
                            nb.r = nr;
                            nb.c = nc;

                            group.blocks += 1;
                            if(board[nr][nc] == 0){
                                group.rainbow += 1;
                            }else{
                                pqB.push(nb); //무지개 블록이 아니어야 기준 블록이 될 수 있음
                                // visited[nr][nc] = true; //rainbow는 방문 처리 안 함 -> num으로 표기
                            }
                            visited[nr][nc] = num; //*****
                            group.v.push_back(nb);
                            q.push(nb);
                        }
                    }
                }

                //pqB에 해당 그룹 정보 담겨 있음, group에는 그룹 정보 담겨 있음 
                if(group.blocks > 1){ //2개 이상
                    Block baseBlock = pqB.top();
                    group.baseR = baseBlock.r;
                    group.baseC = baseBlock.c;

                    pqG.push(group);
                }
            }
        }
    }

    if(pqG.size() == 0){
        return false;
    }else{
        eraseG = pqG.top();
        return true;
    }
}

void Space(){
    for(int c=1; c<=N; c++){
        for(int r=N-1; r>=1; r--){
            if(board[r][c]>=0){ //무지개 블록/색깔 블록
                int num = board[r][c];
                board[r][c] = -2; //빈 칸 표시
                while(r+1<=N){
                    if(board[r+1][c] >= -1){ //블록 만나면 그 전까지만 이동(빈 칸에만 배치 가능!)
                        board[r][c] = num; 
                        break;
                    }
                    r += 1;
                    if(r == N){ //마지막 칸까지 내려왔으면
                        board[r][c] = num;
                    }
                }
            }
        }
    }
}

void Rotate(){
    int temp[21][21];
    
    int nc = 1;
    for(int r=1; r<=N; r++){
        int nr = N;
        for(int c=1; c<=N; c++){
            temp[nr][nc] = board[r][c];
            nr--;
        }
        nc++;
    }

    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++){
            board[r][c] = temp[r][c];
        }
    }
}

int main(){
    int ans = 0;
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> board[i][j];
        }
    }

    while(1){
        if(!FindGroup()){
            break;
        }
        //eliminateG에 제거할 블록 찾기
        ans += eraseG.blocks * eraseG.blocks;
        for(int i=0; i<eraseG.v.size(); i++){
            Block b = eraseG.v[i];
            board[b.r][b.c] = -2; //블록 제거 표시
        }

        Space();
        Rotate();
        Space();
    }

    cout << ans <<"\n";

    return 0;
}