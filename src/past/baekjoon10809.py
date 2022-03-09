def find2(s, string):
    index=0
    for i in range(len(string)):
        if string[i]==s:
            return index
        index+=1 #인덱스는 무조건 증가
    return -1
    
string=str(input())
alph=97
for i in range(26):
    print(find2(chr(alph), string), end=" ")
    alph+=1

"""
string=str(input())
alph=97
for i in range(26):
    print(string.find(chr(alph)), end=" ")
    alph+=1
"""
