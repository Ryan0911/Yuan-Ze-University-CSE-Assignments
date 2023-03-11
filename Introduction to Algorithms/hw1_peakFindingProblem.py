def peakFinding(A, left, right):
    mid = left + (right - left)//2
    tempLow = mid-1
    tempHigh = mid+1
    if(mid+1 == len(A)):
        tempHigh = mid
    elif(mid-1 < 0):
        tempLow = mid
    if(A[mid] < A[tempLow]):
        # only look at left half
        right = mid-1
        return peakFinding(A, left, right)
    elif(A[mid] < A[tempHigh]):
        # only look at right half
        left = mid+1
        return peakFinding(A, left, right)
    else:
        return A[mid]


try:
    while True:
        test = input()
        # ans 20
        # 100,80,60,50,20 ans 100
        # 10,20,30,40,50 ans 50
        # 須判斷corner
        test = test.split(',')
        count = 0
        for i in test:
            test[count] = int(i)
            count += 1
        print("Find it! The peak element is", peakFinding(
            test, left=0, right=len(test)-1))
except EOFError:
    pass
