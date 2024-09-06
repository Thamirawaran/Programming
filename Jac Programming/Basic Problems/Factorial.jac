can Factorial_Recursion(n: int) -> int{
    if n == 1{
        return n;
    }
    else{
        return n* Factorial_Recursion(n-1);
    }
}

can Factorial_Iteration(n: int)-> int{
    let Result =1;
    for i in range(1,n+1){
        Result = Result*i;
    }
    return Result;
}
with entry{
    print(Factorial_Recursion(4));
    print(Factorial_Iteration(4));
}
