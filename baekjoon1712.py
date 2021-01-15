def bep(a,b,c):
    if b>=c:
        print(-1)
    else:
        print(int(a/(c-b)+1))

a, b, c=map(int, input().split()) #공백으로 입력받기
bep(a,b,c)
