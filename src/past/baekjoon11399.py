n=int(input())
times=list(map(int, input().split()))

time=0
accum=0
for i in sorted(times):
    accum+=i
    time+=accum
print(time)
