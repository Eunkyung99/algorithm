answer=int(input())
n=answer
new=-1
count=0
while(new!=answer):
    if(n<10):
        new=(n%10)*10+n
        n=new
        #print(new)
    else:
        new=(n%10)*10+(int(n/10)+n%10)%10
        n=new
        #print(new)
    count+=1

print(count)
