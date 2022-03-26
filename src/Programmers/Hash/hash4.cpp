#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int total[101] = {0,}; //장르별로 플레이 횟수
unordered_map<string, int> um;

struct played{
    int genrePlayed;
    int songPlayed;
    int num;
};

struct compare{
    bool operator()(const played &a, const played &b){
        if(a.genrePlayed == b.genrePlayed){
            if(a.songPlayed == b.songPlayed){
                return a.num > b.num;
            }
            return a.songPlayed < b.songPlayed;
        }
        return a.genrePlayed < b.genrePlayed;
    }
};

priority_queue<played, vector<played>, compare> pq;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    int t = 1; //장르 번호
    for(int i=0; i<genres.size(); i++){
        if(um.find(genres[i]) == um.end()){
            um.insert({genres[i], t++});
        }
        int num = um[genres[i]]; //장르 고유 번호
        total[num] += plays[i]; //재생 횟수 저장
    }
    
    played p;
    
    for(int i=0; i<plays.size(); i++){
        p.genrePlayed = total[um[genres[i]]];
        p.songPlayed = plays[i];
        p.num = i;
        pq.push(p);
    }
    
    int recentGenre = 0;
    int chosedGenre = 0;
    
    while(!pq.empty()){
        played x = pq.top();
        if(x.genrePlayed == recentGenre){
            if(chosedGenre < 2){
                answer.push_back(x.num);
                chosedGenre += 1;
            }
        }else{
            recentGenre = x.genrePlayed;
            chosedGenre = 1;
            answer.push_back(x.num);
        }
        pq.pop();
    }
    
    return answer;
}