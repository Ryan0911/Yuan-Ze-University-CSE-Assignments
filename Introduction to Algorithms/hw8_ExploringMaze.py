import sys


def move(x, y, direction):
    if(direction == 1):  # 左
        return x, y-1
    elif(direction == 3):  # 下
        return x+1, y
    elif(direction == 4):  # 右
        return x, y+1
    elif(direction == 2):  # 上
        return x-1, y


def DFS(start_x, start_y, maze, hall, wid):
    if(maze[start_x][start_y] == "T"):
        maze[start_x][start_y] = "X"
        print(*hall, sep=" ", end="")
        return True
    for i in range(1, 5):
        temp_x, temp_y = move(start_x, start_y, i)
        if(maze[temp_x][temp_y] == "%" or maze[temp_x][temp_y] == "X" or maze[temp_x][temp_y] == "S"):
            continue
        else:
            if(maze[temp_x][temp_y] != "T"):
                maze[temp_x][temp_y] = "X"
            hall.append(str(temp_x * wid + temp_y))
            if(DFS(temp_x, temp_y, maze, hall, wid) == True):
                return True

    hall = hall[:-1]
    return False


if __name__ == "__main__":
    maze2 = sys.stdin.read()
    maze = maze2.split('\n')
    hei = len(maze) - 1
    wid = len(maze[0])
hall = []
for i in range(0, hei):
    maze[i] = list(maze[i])
maze = maze[:-1]
for i in range(0, hei):
    for j in range(0, wid):
        if(maze[i][j] == 'S'):
            start_x = i
            start_y = j
hall.append(str(start_x * wid + start_y))
DFS(start_x, start_y, maze, hall, wid)
