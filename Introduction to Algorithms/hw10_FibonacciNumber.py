try:
    while True:
        data = input()
        data = int(data)
        a = 0
        b = 0
        goal = 0
        for n in range(1, data+1):
            if(n <= 2):
                goal = 1
            else:
                goal = a+b
            a = b
            b = goal
        print(goal)
except EOFError:
    pass
