#include <iostream>
#include <vector>
using namespace std;

int N;
int S[21][21];
int ans = 999999999;

void getScore(int flag){
    int scoreA = 0;
    int scoreB = 0;
    vector<int> A;
    vector<int> B;
    for(int i=1; i<=N; i++){
        if(flag & (1<<i)){
            A.push_back(i);
        }else{
            B.push_back(i);
        }
    }

    for(int i=0; i<A.size(); i++){
        for(int j=i+1; j<A.size(); j++){
            int first = A[i];
            int second = A[j];
            scoreA = scoreA + S[first][second] + S[second][first];
        }
    }

    for(int i=0; i<B.size(); i++){
        for(int j=i+1; j<B.size(); j++){
            int first = B[i];
            int second = B[j];
            scoreB = scoreB + S[first][second] + S[second][first];
        }
    }

    if(abs(scoreA - scoreB) < ans){
        ans = abs(scoreA - scoreB);
    }

}

void DFS(int idx, int count, int flag){
    if(count == N/2){
        getScore(flag);
        return;
    }

    for(int i=idx+1; i<=N; i++){
        DFS(i, count+1, flag | (1 << i));
    }
}
int main(){
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> S[i][j];
        }
    }

    DFS(0, 0, 0);
    
    cout << ans <<"\n";
    return 0;

}