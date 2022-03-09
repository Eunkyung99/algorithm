def fib(n):
    if n<=1:
        return 1
    else:
        return n*fib(n-1)

n=int(input())
print(fib(n))
        
