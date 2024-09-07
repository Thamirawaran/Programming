can pattern(n: int)-> int{
    i = 1;
    while i <= n {
        print("*"*i);
        i +=1;
    }
}

with entry{
    pattern(5);
}
