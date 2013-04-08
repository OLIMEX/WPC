#!/usr/bin/env python

import sys


def get_input(args):
    if len(args) > 1:
        with open(args[1]) as f:
            l = set()
            for line in f:
                l.update(line.split())
            return list(l)
    return [
        'A13-OLinuXino',
        'iMX233-OLinuXino',
        'MOD-PULSE',
        'MOD-IO',
    ]



def subs(s, count):
    """
    return a list of all substrings of string s with count characters
    """
    return [s[i:(i + count)] for i in range(len(s) - count + 1)]


def subs_listset(string_list, sub_len):
    """
    take a list of strings and return a list where every element contains a
    set with all substrings of sub_len chars of the corresponding string.
    """
    return [set(subs(x, sub_len)) for x in string_list]


def unique_code(s, code_len, subset):
    for i in range(len(s) - code_len):
        code = s[i:(i + code_len)]
        if code not in subset:
            return code
    return None


if __name__ == '__main__':
    """
    without arguments uses input_list global variable, otherwise an input_list
    of string will be created with every words in the file passed as first
    argument.
    """
    input_list = get_input(sys.argv)
    output_codes = []
    lower_input = [s.lower() for s in input_list]
    input_len = len(lower_input)
    sub_len = 1
    subsets = subs_listset(lower_input, sub_len)
    for i, s in enumerate(lower_input):
        code = None
        for j in range(1, len(s)):
            if j > sub_len:
                sub_len += 1
                subsets = map(lambda x, y: x.union(y), subsets,
                           subs_listset(lower_input, sub_len))
            # ignore the subset relative to the string s
            ignore = subsets.pop(i)
            # create a unique big set with all possible substrings
            bigset = reduce(lambda x, y: x.union(y), subsets)
            # try if a code of sub_len chars exists
            code = unique_code(s, j, bigset)
            # reinsert the subset
            subsets.insert(i, ignore)
            if code:
                output_codes.append(code)
                break
        if not code:
            output_codes.append('None')
        print((s, code))

