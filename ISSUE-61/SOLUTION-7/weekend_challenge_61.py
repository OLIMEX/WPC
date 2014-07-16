variations = ['+', '-', '']
equation = '1%s2%s3%s4%s5%s6%s7%s8%s9'

for c1 in variations:
    for c2 in variations:
        for c3 in variations:
            for c4 in variations:
                for c5 in variations:
                    for c6 in variations:
                        for c7 in variations:
                            for c8 in variations:
                                if int(eval(equation % (c1, c2, c3, c4, c5, c6, c7, c8))) == 100:
                                    print equation % (c1, c2, c3, c4, c5, c6, c7, c8)
                                    #print(equation % (c1, c2, c3, c4, c5, c6, c7, c8))  # Python3