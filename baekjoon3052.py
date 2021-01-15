mod=[]
for i in range(10):
    n=int(input())
    n=n%42
    if n not in mod:
        mod.append(n)
print(len(mod))
