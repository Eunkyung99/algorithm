n=int(input())
v=int(input())
graph=[[0 for i in range(n+1)] for i in range(n+1)]
for i in range(v):
    a, b=map(int, input().split())
    graph[a][b]=1
    graph[b][a]=1

def bfs(graph, start):
    queue=[start]
    visited=[]
    while queue:
        tmp=queue.pop(0)
        visited.append(tmp)
        for i in range(len(graph)):
            if graph[tmp][i] and i not in visited and i not in queue:
                queue.append(i)

    return len(visited)-1

print(bfs(graph, 1))
