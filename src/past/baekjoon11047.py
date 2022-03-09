n, k=map(int, input().split())
coin=[]
for i in range(n):
    coin.append(int(input()))
count=0
index=len(coin)-1
"""while k>0:
    if k<coin[index]:
        index-=1
        continue
    k-=coin[index]
    count+=1
"""
while k>0:
    if k<coin[index]:
        index-=1
        continue
    count+=int(k/coin[index])
    k%=coin[index]

print(count)
