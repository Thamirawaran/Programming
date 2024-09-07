can fun(value: int){
    if value < 0 {
        raise ValueError("Value must be non negative");
    }
}

with entry{
    try{
        fun(-4);
    }
    except ValueError as error{
        print(error);
    }
}
