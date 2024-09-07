can voter_id(age: int)-> str{
    if age >= 18{
        return "you can vote";
    }
    elif age >=16 {
        return "You can apply for voter id";
    }
    else{
        return "You have to wait";
    }
}
with entry{
    Age = 15;
    print(voter_id(Age));
}
