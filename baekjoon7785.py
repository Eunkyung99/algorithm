n=int(input())
enterlist={} #딕셔너리
for i in range(n):
    a, b=map(str, input().split())
    if b=="enter":
        enterlist[a]=True
    else:
        del enterlist[a]
for i in sorted(enterlist.keys(), reverse=True):
        print(i)
