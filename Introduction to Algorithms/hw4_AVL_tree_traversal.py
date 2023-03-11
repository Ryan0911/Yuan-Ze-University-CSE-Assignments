
class node():
    def __init__(self, value=None):
        self.left = None
        self.right = None
        self.height = 0
        self.val = value


class AVL_Tree():
    def __init__(self):
        self.root = None
        self.value = 0

    def insert(self, value):
        if(self.root == None):
            self.root = node(value)
        else:
            self.__insert(self.root, value, None)

    def __insert(self, current_node, value, parent_node):
        if(current_node.val > value):
            if(current_node.left != None):
                self.__insert(current_node.left, value, current_node)
            else:
                current_node.left = node(value)
        elif(current_node.val < value):
            if(current_node.right != None):
                self.__insert(current_node.right, value, current_node)
            else:
                current_node.right = node(value)
        else:
            print("exists")
        current_node.height = self.getHeight(current_node)
        balanceFactor = self.getHeight(
            current_node.left) - self.getHeight(current_node.right)
        if(balanceFactor > 1):  # 左較重
            balanceFactor = self.getHeight(
                current_node.left.left) - self.getHeight(current_node.left.right)
            if(balanceFactor > 0):  # LL
                if(parent_node == None):
                    self.root = self.rightRotate(current_node)
                else:
                    if(self.getBalance(parent_node) < 0):
                        parent_node.right = self.rightRotate(current_node)
                    else:
                        parent_node.left = self.rightRotate(current_node)
            else:  # LR
                current_node.left = self.leftRotate(current_node.left)
                if(parent_node == None):
                    self.root = self.rightRotate(current_node)
                else:
                    if(self.getBalance(parent_node) < 0):
                        parent_node.right = self.rightRotate(current_node)
                    else:
                        parent_node.left = self.rightRotate(current_node)
        elif(balanceFactor < -1):  # 右重
            balanceFactor = self.getHeight(
                current_node.right.left) - self.getHeight(current_node.right.right)
            if(balanceFactor < 0):  # RR
                if(parent_node == None):
                    self.root = self.leftRotate(current_node)
                else:
                    if(self.getBalance(parent_node) < 0):
                        parent_node.right = self.leftRotate(current_node)
                    else:
                        parent_node.left = self.leftRotate(current_node)
            else:  # RL
                current_node.right = self.rightRotate(current_node.right)
                if(parent_node == None):
                    self.root = self.leftRotate(current_node)
                else:
                    if(self.getBalance(parent_node) < 0):
                        parent_node.right = self.leftRotate(current_node)
                    else:
                        parent_node.left = self.leftRotate(current_node)

    def getHeight(self, node):
        if(node == None):
            return -1
        return max(self.getHeight(node.left), self.getHeight(node.right)) + 1

    def getBalance(self, node):
        return self.getHeight(node.left) - self.getHeight(node.right)

    def leftRotate(self, current_node):
        x = current_node.right
        temp = x.left
        x.left = current_node
        current_node.right = temp
        x.height = self.getHeight(x)
        current_node.height = self.getHeight(current_node)
        return x

    def rightRotate(self, current_node):
        x = current_node.left
        temp = x.right
        x.right = current_node
        current_node.left = temp
        x.height = self.getHeight(x)
        current_node.height = self.getHeight(current_node)
        return x


def inorder_traversal(ans, avl_tree):
    if(avl_tree.left != None):
        inorder_traversal(ans, avl_tree.left)
    ans.append(avl_tree.val)
    if(avl_tree.right != None):
        inorder_traversal(ans, avl_tree.right)
    return ans


try:
    while True:
        test = input()
        test = test.split(',')
        count = 0
        # 41,20,65,11,29,50,26,23
        for i in test:
            test[count] = int(i)
            count += 1
        avlTree = AVL_Tree()
        for i in test:
            avlTree.insert(i)
        ans = []
        ans = inorder_traversal(ans, avlTree.root)
        print("Inorder traversal: [", ", ".join(str(item)
                                                for item in ans), "]", sep="")
except EOFError:
    pass
