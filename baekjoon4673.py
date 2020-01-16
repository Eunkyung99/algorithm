def d(n):
    sum=n
    while n>0:
        sum+=int(n%10)
        n/=10
    return sum

numbers=set(range(1, 10001)) #1부터 10000까지 생성
init=set() #빈 집합 생성

i=1
while d(i)<=10040: #9999의 경우 d(i)의 값이 10035
    init.add(d(i))
    i+=1
selfnumber=numbers-init

for i in sorted(selfnumber):
    print(i)
