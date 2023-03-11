def h1(k):
    return k % 13


def h2(k):
    return 1+(k//13) % (13-1)


def hash_(k, i):
    return (int(h1(k) + i*h2(k))) % 13


def search(num, array):
    for i in array:
        if(i == num):
            return True
    return False


try:
    while True:
        data = input()
        data = data.split(',')
        m = 13
        hashList = []
        compare_size = 0
        for i in range(0, m):
            hashList.append(None)
        for i in data:
            if(compare_size == m):
                break
            k = int(i)
            if(search(k, data) == True):
                continue
            if(hashList[hash_(k, 0)] == None):
                hashList[hash_(k, 0)] = k
                compare_size += 1
            else:
                collision_pos = k
                i2 = 1
                while(True):
                    if(hashList[hash_(k, i2)] == None):
                        hashList[hash_(k, i2)] = k
                        compare_size += 1
                        print("Collision has occurred for element {} at position {} finding new Position at position {}".format(
                            collision_pos, hash_(collision_pos, 0), hash_(k, i2)))
                        break
                    i2 += 1
        print("Done")
except EOFError:
    pass
