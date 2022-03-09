def word_check(word):
    char=[]
    index=[]
    for i in range(len(word)):
        if word[i] in char:
            idx=char.index(word[i])
            if i==index[idx]+1:
                index[idx]=i
            else :
                return False
        else:
            char.append(word[i])
            index.append(i)
    return True
    
n=int(input())
count=0
for i in range(n):
    word=input()
    if word_check(word) :
        count+=1

print(count)
