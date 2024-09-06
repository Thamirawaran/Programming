#Sum of the first nth term of Series
def series_sum(n):
    i=0.00
    k=1
    for j in range(n):
        i+=(1/k)
        k+=3
    return "%.2f"%(i)
