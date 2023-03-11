try:
    while True:
        data = input()
        data = data.split(',')
        source = data[len(data)-2]
        target = data[len(data)-1]
        data = data[:len(data)-2]
        # print(data)
        dist = []
        visit = []
        for i in range(26):
            dist.append(float("inf"))
            visit.append(0)
        edgeA = "0"
        edgeB = "0"
        weight = 0
        flag = [dist.copy() for i in range(26)]
        for i in range(0, len(data), 3):
            edgeA = ord(data[i])-65
            edgeB = ord(data[i+1])-65
            weight = int(data[i+2])
            flag[edgeA][edgeB] = weight
        dist[ord(source)-65] = 0
        #visit[ord(source)-65] = 1
        # for index, i in enumerate(flag[ord(source)-65]):
        # if(i != float("inf")):
        #dist[index] = i
        for i in range(0, 26):
            min_num = float("inf")
            for j in range(0, 26):
                if(visit[j] == 0 and dist[j] < min_num):
                    min_num = dist[j]
                    path = j
            visit[path] = 1
            for k in range(0, 26):
                if(dist[k] > dist[path] + flag[path][k]):
                    dist[k] = dist[path] + flag[path][k]
        # 輸出
        print("The shortest distance from {} to {} is {}".format(
            source, target, dist[ord(target)-65]))
except EOFError:
    pass
