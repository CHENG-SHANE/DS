#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;

template<class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class BinaryTreeNode : public Node<T>
{
public:
	BinaryTreeNode() : Node<T>()
	{
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(T d) : Node<T>(d)
	{
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>()
	{
		left = l;
		right = r;
	}
	BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d)
	{
		left = l;
		right = r;
	}
	void setLeft(BinaryTreeNode<T> *l)
	{
		left = l;
	}
	void setRight(BinaryTreeNode<T> *r)
	{
		right = r;
	}
	BinaryTreeNode<T> *&getLeft()
	{
		return left;
	}
	BinaryTreeNode<T> *&getRight()
	{
		return right;
	}
	bool operator>(BinaryTreeNode<T> n)
	{
		if(*(this->data) > *(n.data))
			return true;
		return false;
	}
	bool operator==(BinaryTreeNode<T> n)
	{
		if(*(this->data) == *(n.data))
			return true;
		return false;
	}
private:
	BinaryTreeNode<T> *left, *right;
};


template<class T>
class AVLTree {
private:
    BinaryTreeNode<T> *root; // AVL 樹的根節點

	// 計算樹的高度
    int height(BinaryTreeNode<T> *N) {
        if (N == NULL)
            return 0;
        return max(height(N->getLeft()), height(N->getRight())) + 1;
    }

	// 判斷樹是否平衡 1 0 -1
    int getBalance(BinaryTreeNode<T> *N) {
        if (N == NULL)
            return 0;
        return height(N->getLeft()) - height(N->getRight());
    }

    // 右旋轉
    BinaryTreeNode<T>* rightRotate(BinaryTreeNode<T> *y) {
        BinaryTreeNode<T> *x = y->getLeft();
        BinaryTreeNode<T> *T2 = x->getRight();
		
        // 執行旋轉
        x->setRight(y);
        y->setLeft(T2);
		
        // 返回新的根節點
        return x;
    }
	
    // 左旋轉
    BinaryTreeNode<T>* leftRotate(BinaryTreeNode<T> *x) {
        BinaryTreeNode<T> *y = x->getRight();
        BinaryTreeNode<T> *T2 = y->getLeft();
        y->setLeft(x);
        x->setRight(T2);
        return y;
    }
	
    // 插入函數
    BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, T key) {
        if (node == NULL)
            return(new BinaryTreeNode<T>(key)); // 如果節點為空，創建新節點
		
        // 插入
        if (key < node->getData())
            node->setLeft(insert(node->getLeft(), key));
        else if (key > node->getData())
            node->setRight(insert(node->getRight(), key));
        else 
            return node; // 如果值已存在，則返回當前節點
		
        int balance = getBalance(node); // 計算平衡
		
        // 四種旋轉情況
        // LL
        if (balance > 1 && key < node->getLeft()->getData())
            return rightRotate(node);
		
        // RR
        if (balance < -1 && key > node->getRight()->getData())
            return leftRotate(node);
		
        // LR
        if (balance > 1 && key > node->getLeft()->getData()) {
            node->setLeft(leftRotate(node->getLeft()));
            return rightRotate(node);
        }
		
        // RL
        if (balance < -1 && key < node->getRight()->getData()) {
            node->setRight(rightRotate(node->getRight()));
            return leftRotate(node);
        }
		
        return node; // 返回根節點
    }

    // 中序遍歷
    void inorder(BinaryTreeNode<T> *cur, int n) {
        if(cur == NULL)
            return; // 如果當前節點為空，則返回
        inorder(cur->getRight(), n + 1); // 遍歷右子樹
        cout << cur->getData() << " " << endl; // 輸出節點數據
        inorder(cur->getLeft(), n + 1); // 遍歷左子樹
    }

public:
    AVLTree() {
        root = NULL; // 初始化根節點為空
    }

    // 插入元素
    void insert(T key) {
        root = insert(root, key); // 調用插入函數
    }

    // 中序遍歷
    void inorder() {
        inorder(root, 0); // 從根節點開始中序遍歷
    }
};


int main()
{
	cout<<"star"<<endl;
	AVLTree<int> *tree = new AVLTree<int>();
	srand(time(NULL));
	int j, k, i;
	for(j = 0;j < 100;j ++)
	{
		tree->insert(rand() % 1000);
		tree->inorder();
		cout<<"----------------"<<endl;
	}
}
