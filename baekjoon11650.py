class coord:
    x=0
    y=0

n=int(input())
list=[]
for i in range(n):
    c1=coord()
    c1.x, c1.y=map(int, input().split())
    list.append(c1)
"""
for k in range(n-1):
    for i in range(n-1):
        j=i+1
        if list[i].x>list[j].x:
            c=coord()
            c=list[i]
            list[i]=list[j]
            list[j]=c
        elif list[i].x==list[j].x:
            if list[i].y>list[j].y:
                c=coord()
                c=list[i]
                list[i]=list[j]
                list[j]=c
"""
list=sorted(list, key=lambda c:(c.x, c.y))
for i in range(n):
    print(list[i].x, list[i].y)
