can fun(){
    yield "Hello";
    yield 10;
    yield 100;
    # yield ;
}

with entry{
    x = fun();
    print(x);
    for i in x{
        print(i);
    }
}
