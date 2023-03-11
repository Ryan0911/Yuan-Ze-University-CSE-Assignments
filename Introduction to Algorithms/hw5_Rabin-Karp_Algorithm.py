# input:
# Searching for Patterns,rchi,101,256
# Smartphone photo,ph,101,256

# output:
# Pattern found at index 3
# Done
# Pattern found at index 5
# Pattern found at index 11
# Done
def compare(s1, s2, m):
    if(hash_function(s1, m) == hash_function(s2, m)):
        return True
    return False


def hash_function(s, m):
    power = len(s) - 1
    total = 0
    for i in s:
        total += ord(i) ** power
        power -= 1
    return total % m


try:
    while True:
        data = input()
        data = data.split(',')
        txt = data[0]
        sub_string = data[1]
        hash_table = data[2]
        alphabet = data[3]
        find_length = len(sub_string)
        rt = txt[:len(sub_string)]
        equal = True
        if(compare(rt, sub_string, int(hash_table))):
            for i2 in range(0, len(sub_string)):
                if(rt[i2] != sub_string[i2]):
                    equal = False
                    break
            if(equal == True):
                print("Pattern found at index 0")
            equal = True
        for i in range(len(sub_string), len(txt)):
            rt = rt[1:]
            rt += txt[i]
            if(compare(sub_string, rt, int(hash_table))):
                for i2 in range(0, len(sub_string)):
                    if(rt[i2] != sub_string[i2]):
                        equal = False
                        break
                if(equal == True):
                    print("Pattern found at index {}".format(i-len(sub_string)+1))
                equal = True
        print("Done")
except EOFError:
    pass
