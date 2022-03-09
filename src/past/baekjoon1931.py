n=int(input())
class sf:
    start=0
    finish=0
schedule=[]
for i in range(n):
    sf1=sf() #객체 생성
    sf1.start, sf1.finish=map(int, input().split())
    schedule.append(sf1)
schedule=sorted(schedule, key=lambda sf:(sf.finish, sf.start)) #일찍 끝나는 순으로 정렬
count=1
f=schedule[0].finish #처음 끝나는 시간
i=1 #인덱스
while i<n:
    if f<=schedule[i].start:
        f=schedule[i].finish
        i+=1
        count+=1
    else:
        i+=1 #인덱스 증가

print(count)
