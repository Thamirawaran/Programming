def longest_consec(s, k):
    m=""
    if len(s)<k or k<0:
        pass
    else:
        for i in range(len(s)-k+1):
            Sub="".join(s[i:i+k])
            if len(m)<len(Sub):
                m=Sub
    return m
