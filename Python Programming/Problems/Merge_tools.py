def merge_the_tools(string, k):
    def unique(string):
        List=list(string)
        N_List=[]
        for i in List:
            if i not in N_List:
                N_List.append(i)
        return ''.join(N_List)
    UList=[string[i*k:(i+1)*k] for i in range(int(len(string)/k))]
    for i in UList:
        print(unique(i))
