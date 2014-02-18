# # http://en.wikipedia.org/wiki/Bank_card_number
# http://en.wikipedia.org/wiki/ISO/IEC_7812
# http://en.wikipedia.org/wiki/Luhn_algorithm
def luhn_checksum(card_number):
    digits = [int(d) for d in str(card_number)]
    return (sum(digits[-1::-2]) + sum([sum([int(n) for n in str(d*2)]) for d in digits[-2::-2]])) % 10
 
def is_luhn_valid(card_number):
    return luhn_checksum(card_number) == 0

# for testing
#for i in range(10):
#    print i, is_luhn_valid("7992739871" + str(i)) # 3 is True

#def calculate_luhn(partial_card_number):
#    check_digit = luhn_checksum(int(partial_card_number) * 10)
#    return 0 if check_digit == 0 else 10 - check_digit

def is_in_iin(card_number):
# http://en.wikipedia.org/wiki/List_of_Bank_Identification_Numbers
# Unfortunately, data from BINDB.com is not free
    list_iin6 = { \
        "540716":"ktc", \
        "493112":"ktc", \
        "544572":"bay", \
        "403375":"uob", \
        "464009":"uob", \
        "464005":None, \
        "464006":None, \
        "464007":None, \
        "479000":"Bulgarian Postbank", \
        }
    list_iin4 = { \
        "5200":0, \
        "5211":0, \
        "5217":0, \
        }
    return card_number[0:6] in list_iin6 or card_number[0:4] in list_iin4

def is_card_valid(card_number):
    return is_luhn_valid(card_number) and is_in_iin(card_number)

for i in range(10):
    print i, "Valid" if is_card_valid("540716999999999" + str(i)) else "Invalid"
