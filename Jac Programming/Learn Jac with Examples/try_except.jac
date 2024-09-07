can division(a: int, b: int)-> int{
    try {
        return a / b;
    }
    except Exception as error{
        return error;
    }
}

with entry{
    print(division(10, 0));
}
