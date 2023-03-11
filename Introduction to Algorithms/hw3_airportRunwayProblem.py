class BST_Node:
    def __init__(self, val=None):
        self.left = None
        self.right = None
        self.val = val


class BST:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root == None:
            self.root = BST_Node(value)
        else:
            self._insert(self.root, value)

    def _insert(self, current_node, value):
        if(value < current_node.val):
            if(current_node.left == None):
                current_node.left = BST_Node(value)
            else:
                self._insert(current_node.left, value)
        elif(value > current_node.val):
            if(current_node.right == None):
                current_node.right = BST_Node(value)
            else:
                self._insert(current_node.right, value)
        else:
            print("node existed")


def get_min(current_node):
    current_node = current_node.root
    while(current_node.left != None):
        current_node = current_node.left
    return current_node.val


def search_k(current_node, value, k):
    if(value < get_min(current_node)):
        return False
    current_node = current_node.root
    while(current_node != None):
        if((value-k) < current_node.val < (value+k)):
            return False
        if(value < current_node.val):
            current_node = current_node.left
        elif(value > current_node.val):
            current_node = current_node.right
        else:
            print("node existed")
            return False
    return True


try:
    while True:
        landing = input()
        # 5,37,41,46,49,56,3,44,53,20
        landing = landing.split(',')
        #count = 0
        size = len(landing)
        count = 0
        for i in landing:
            landing[count] = int(i)
            count += 1
        N = landing[0]
        k = landing[N+1]
        my_data = BST()
        for i in range(1, N+1):
            my_data.insert(landing[i])
        for i in range(N+2, (N+2)+k):
            if(search_k(my_data, landing[i], k) == True):
                print("Request at time", landing[i], "is allowed")
            else:
                print("Request at time", landing[i], "is not allowed")
except EOFError:
    pass
