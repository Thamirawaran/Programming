can odd_even(a: int)-> int {
    if a % 2 == 0{
        return "Even";
    }
    else {
        return "Odd";
    }
}

with entry {
    print(odd_even(10));
}
