#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdio>
#include <vector> 
#include <algorithm>
#include <sstream>

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
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL){
			at->getNext()->setPrev(node);
		}
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL){
			tail = node;
		}
	}
	ListNode<T> *removeFromHead(){
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			cout<<(*j)<<" ";
			j = j->getNext();
		}
		cout<<endl;
	}

protected:
	ListNode<T> *head, *tail;
};

template<class T>
class GraphNode : public Node<T>
{
public:
	GraphNode() :Node<T>()
	{
		list = new LinkList<T>();
	}
	GraphNode(T d) :Node<T>(d)
	{
		list = new LinkList<GraphNode<T> *>();
	}
	void addLink(GraphNode<T> *node)
	{
		list->addFromTail(node);
	}
	bool exist(GraphNode<T> *node)
	{
		if(list->exist(node))
			return true;
		return false;
	}
	void remove(GraphNode<T> *node)
	{
        list->remove(list->exist(node));

	}
	ListNode<GraphNode<T> *> *operator[](int n)
	{
		try
		{
            return &(*list)[n];
		}
		catch(invalid_argument e)
		{
			return NULL;
		}
	}
private:
	LinkList<GraphNode<T> *> *list;
};

template<class T>
class Graph{
public:
	Graph()
	{
		vertex = new LinkList<GraphNode<T> *>();
		count = 0;
	}
	// 增加一個節點
	GraphNode<T> *addVertex(T d)
	{
		GraphNode<T> *node = new GraphNode<T>(d);
		vertex->addFromTail(node);
		count ++;
		return node;
	}
	//增加點與點之間的連結
	void addLink(GraphNode<T> *node1, GraphNode<T> *node2)
	{
		node1->addLink(node2);
		node2->addLink(node1);
	}
	//檢查兩點是否有連結
	bool isLinked(GraphNode<T> *node1, GraphNode<T> *node2)
	{
		return node1->exist(node2);
	}

	// 抓取第n個節點
	GraphNode<T> *operator[](int n)
	{
		try
		{
			// 返回第n個節點
			return (*vertex)[n].getData();
		}
		catch(invalid_argument e)// 如果沒有這個節點，就返回NULL
		{
			return NULL;
		}
	}
	
    void adjMatrix(){
		// 建立一個二維陣列(表示連接關係用的)
        int **matrix = new int*[count];
        for(int i = 0; i < count; i++) {
            matrix[i] = new int[count];
            for(int j = 0; j < count; j++) {
                matrix[i][j] = 0;
            }
        }
		
		// 把連接關係放進二維陣列裡
		// 抓取每個節點
		for(int i = 0; i < count; i++) {
			GraphNode<T> *node = (*this)[i];
			ListNode<GraphNode<T> *> *adjNode = (*node)[0];// 抓取節點的第一個鄰接節點
			
			//遍歷當前節點的所有鄰接節點
			while(adjNode != NULL) {// 表示還有鄰接節點
				int j = 0;
				
				// 在節點列表中查找鄰接節點的索引直到找到才會退出
				while((*this)[j] != adjNode->getData() && j < count) {
					j++;
				}
				
				// 如果找到鄰接節點，則在鄰接矩陣中標記連接21                                                                        
				if (j < count) {
					matrix[i][j] = 1; // 標記節點 i 和節點 j 之間有連接
				}
				
				// 移動到下一個節點
				adjNode = adjNode->getNext();
			}
		}
		
        for(int i = 0; i < count; i++) {
            for(int j = 0; j < count; j++) {
                cout << matrix[i][j];
            }
            cout << endl;
        }
    }

	void adjList(){
		for(int i = 0; i < count; i++) {
			ostringstream line;
			line << i << ":";
			
			vector<int> neighbors; // 存儲鄰居節點索引的向量
			
			GraphNode<T> *node = (*this)[i]; // 獲取當前節點
			ListNode<GraphNode<T> *> *adjNode = (*node)[0]; // 獲取當前節點的第一個鄰接節點
			
			// 遍歷當前節點的所有鄰接節點
			while(adjNode != NULL) {
				GraphNode<T> *adjGraphNode = adjNode->getData(); // 獲取鄰接節點
				
				for (int j = 0; j < count; j++) {
					if ((*this)[j] == adjGraphNode) { // 如果節點 j 是鄰接節點
						//避免重複添加鄰居節點
						if (find(neighbors.begin(), neighbors.end(), j) == neighbors.end()) {
							neighbors.push_back(j);
						}
						break;
					}
				}
				
				adjNode = adjNode->getNext(); // 移動到下一個
			}
			
			sort(neighbors.begin(), neighbors.end());
			
			for (int k = 0; k < neighbors.size(); k++) {
				line << neighbors[k] << " ";
			}
			cout << line.str() << endl; // 輸出鄰接列表
		}
	}

private:
	LinkList<GraphNode<T> *> *vertex;//頂點
	int count;
};

int main()
{
	cout << "start\n";
    Graph<int> *g = new Graph<int>();
    LinkList<GraphNode<int> *> *node = new LinkList<GraphNode<int> *>();
    
	int j, k, s, a, b, n;
    scanf("%d", &s);
    srand(s);
	
	//創建要測試的節點
    n = rand() % 50;
    for(j = 0;j < n;j ++)
        node->addFromTail(g->addVertex(j + 1));
	
	//創建節點之間的的連結數量
    k = rand() % 100;
    for(j = 0;j < k;j ++){
		//抽兩個節點建立關係
        a = rand() % n;
        b = rand() % n;
        g->addLink(((*node)[a]).getData(), ((*node)[b]).getData());
    }
	
    g->adjMatrix();
    g->adjList();
	
	cout << "end\n";
	
	return 0;
}