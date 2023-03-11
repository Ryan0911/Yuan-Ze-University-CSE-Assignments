def move(x, y, direction):
    if(direction == 1):
        return x-2, y+1
    elif(direction == 2):
        return x-1, y+2
    elif(direction == 3):
        return x+1, y+2
    elif(direction == 4):
        return x+2, y+1
    elif(direction == 5):
        return x-1, y-2
    elif(direction == 6):
        return x-2, y-1
    elif(direction == 7):
        return x+1, y-2
    return x+2, y-1

# x y => 0<= x,y <=7


def BFS(flag, start_x, start_y, end_x, end_y):
    flag[start_x][start_y] = 1
    froniter = [[start_x, start_y]]
    target = 0
    parent = {(str(start_x)+str(start_y)): None}
    while(froniter):
        next = []
        for u in froniter:
            for v in range(1, 9):
                d_x, d_y = move(u[0], u[1], v)
                if(d_x >= 0 and d_x <= 7 and d_y >= 0 and d_y <= 7):
                    if(flag[d_x][d_y] != 1):
                        flag[d_x][d_y] = 1
                        parent[(str(d_x)+str(d_y))] = ((str(u[0])+str(u[1])))
                        next.append(move(u[0], u[1], v))
                if(d_x == end_x and d_y == end_y):
                    target2 = (str(d_x)+str(d_y))
                    while parent[target2] != None:
                        target += 1
                        target2 = parent[target2]
                    return target
        froniter = next
    return target


try:
    while True:
        data = input()
        data = data.split(',')
        flag = [[0, 0, 0, 0, 0, 0, 0, 0] for i in range(9)]
        start_x = int(data[0])
        start_y = int(data[1])
        end_x = int(data[2])
        end_y = int(data[3])
        target = BFS(flag, start_x, start_y, end_x, end_y)
        print("To get from Point( {} , {} ) to Point( {} , {} ) takes {} knight moves.".format(
            start_x, start_y, end_x, end_y, target))
except EOFError:
    pass
