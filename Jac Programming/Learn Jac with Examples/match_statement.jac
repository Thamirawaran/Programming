can week(day: int)-> str{
    match day {
        case 1 : 
            return "Monday";
        case 2 : 
            return "Tuesday";
        case 3 : 
            return "Wednesday";
        case 4 : 
            return "Thursday";
        case 5 : 
            return "Friday";
        case 6 : 
            return "Saturday";
        case 8 : 
            return "Sunday";
        case _ : 
            return "Wrong input";
    }
}

with entry{
    print(week(1));
}
