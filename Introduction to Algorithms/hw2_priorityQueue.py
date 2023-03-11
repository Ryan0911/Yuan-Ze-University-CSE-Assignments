def compareChild(left, right):
    if(left < right):
        return 0
    else:
        return 1


def max_heapify(A, n):
    left = n*2
    right = n*2+1
    if(left > len(A)):
        return A
    if(right > len(A)):
        right = left
    if(compareChild(A[left-1], A[right-1]) == 1):
        MAX = left
    else:
        MAX = right
    if(A[n-1] < A[left-1] or A[n-1] < A[right-1]):
        A[n-1], A[MAX-1] = A[MAX-1], A[n-1]
        return max_heapify(A, MAX)


try:
    while True:
        A = input()
        # 2,4,1
        # 16,14,10,8,7,9,3,2,4,1
        A = A.split(',')
        #count = 0
        size = len(A)
        count = 0
        for i in A:
            A[count] = int(i)
            count += 1
        for i in range(len(A)//2, 0, -1):
            max_heapify(A, i)
        #sortedArray = []
        # for i in range(0, len(A)):
        #    sortedArray.append(A[0])
        #    A[0], A[len(A)-1] = A[len(A)-1], A[0]
        #    A = A[:-1]
        #    max_heapify(A, 1)
        print(
            "The array representation of the heap is [", end='')
        print(*A, sep=' ', end='')
        print("]")
except EOFError:
    pass
