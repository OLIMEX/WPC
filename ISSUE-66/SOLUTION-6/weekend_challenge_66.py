def print_row(symbol, times, rest):
    print symbol*times + rest


def tree_row(elements):
    row = '/'
    if elements == 0:
        row += '_\\'
    else:
        for i in range(elements):
            row += '_' + ("\\" if elements % 2 == 0 else "/")
        row += "_\\"
    print_row(' ', 14 - elements, row)

print_row(' ', 14, "\ /")  # The top
print_row(' ', 12, "-->*<--")  # The topweek
# Draw each row
for i in range(10):
    tree_row(i)
print_row(' ', 13, "[___]")

