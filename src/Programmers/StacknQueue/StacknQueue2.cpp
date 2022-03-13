#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Info{
    int value;
    bool isloc;
};

struct compare{
    bool operator()(const Info& a, const Info& b){
        if(a.value < b.value){
            return true;
        }
        return false;
    }
};

int solution(vector<int> priorities, int location) {
    int answer = 0;
    vector<Info> v;
    priority_queue<Info, vector<Info>, compare> q;
    int before = 0;
    Info info;
    
    for(int i=0; i<priorities.size(); i++){
        info.value = priorities[i];
        if(i == location){
            info.isloc = true;
        }else{
            info.isloc = false;
        }
        q.push(info);
        v.push_back(info);
    }
    
    while(!q.empty()){
        info = q.top();
        Info i = v[0]; 
        v.erase(v.begin()+0);
        if(i.value < info.value){
            v.push_back(i); //인쇄 안 됨
        }else if(i.value == info.value){
            if(i.isloc){
                answer++;
                break;
            }
            q.pop();
            answer++;
        }else{
            q.pop();
            answer++;
        }
    }
    
    
    return answer;
}