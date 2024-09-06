n = int(input())
arr = list(map(int, input().split()))
n=arr.count(max(arr))
i=0
while i<n:
    arr.remove(max(arr))
    i+=1
a=max(arr)
print(a)
