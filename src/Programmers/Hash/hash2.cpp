#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool solution(vector<string> phone_book) {
    unordered_map<string, int> um;
    
    for(int i=0; i<phone_book.size(); i++){
        um[phone_book[i]] = 1;      
    }
    
    for(int i=0; i<phone_book.size(); i++){
        string s = "";
        for(int j=0; j<phone_book[i].size() - 1; j++){ //***** i의 길이-1
            s = s + phone_book[i][j];
            if(um[s] == 1){
                return false;
            }
        }
    }
    return true;
}