n,m=input().split(" ")
C=list(input().split(" "))
A=set(input().split(" "))
B=set(input().split(" "))

H=0
for i in C:
    if i in A:
        H+=1
    elif i in B:
        H-=1
print(H)
