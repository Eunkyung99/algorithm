def calculate():
    result=str(input())
    count=[0 for i in range(len(result))]
    score=0
    for i in range(len(result)):
        if i==0 and result[i]=="O":
            count[i]=1
        elif result[i]=="O":
            if result[i-1]=="O":
                count[i]=count[i-1]+1
            else:
                count[i]=1
    for i in range(len(result)):
        score+=count[i]
    print(score)

testcase=int(input())
for i in range(testcase):
    calculate()
